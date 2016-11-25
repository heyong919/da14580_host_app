#include "stdtypes.h"
#include "app_msg.h"
#include "transport.h"

#define SEND_BUFF_SIZE  (1024)
#define RECV_BUFF_SIZE  (1024)
#define MSG_QUEUE_SIZE (32)

#define SERIAL_SINGLE_RW_LEN  256

static char *recv_buff;
static char *send_buff;
//static int16_t recv_r, recv_w, send_r, send_w;
static ringbuffer_t send_rb, recv_rb;

#undef QUEUE_TYPE
#define QUEUE_TYPE  stack_msg_t*
#include <queue.h>

static stack_msg_t* msg_queue_buffer[MSG_QUEUE_SIZE];
static queue_t msg_queue;

static int32_t handle=-1;


int32_t transport_ready_to_read() {
  int32_t rd_num, buf_size;
  char *buf;
  char packet_head[sizeof(stack_msg_t)+1]; // 9 bytes
  stack_msg_t *msg;

  if(handle < 0)
    return -1;
  buf = mem_alloc(SERIAL_SINGLE_RW_LEN);
  buf_size = rb_available_space(&recv_rb);
  while(buf_size > 0) {
    if(buf_size > SERIAL_SINGLE_RW_LEN)
      buf_size = SERIAL_SINGLE_RW_LEN;

    rd_num = serial_read(handle, buf, buf_size);
    //printf("read[%d]: %s\n", rd_num, recv_buff);

    if(rb_write(&recv_rb, buf, rd_num) < 0)
      dbg_printf("rb_write failed!\n");
    if(rd_num < buf_size)
      break;

    buf_size = rb_available_space(&recv_rb);
  }
  mem_free(buf);

  while(rb_remaining_data(&recv_rb) > sizeof(packet_head)) {
    if(rb_read_prepare(&recv_rb, packet_head, sizeof(packet_head)) == 0) {
      if(packet_head[0] == FIXED_PACKET_HEAD) {
        // msg_len exclude packet header
        // this is to ensure message data aligned
        int32_t msg_len = sizeof(stack_msg_t) + packet_head[7] + (packet_head[8]<<8);
        if(rb_remaining_data(&recv_rb) >= msg_len) {
          rb_read_commit(&recv_rb, 1); // skip packet header
          buf = mem_alloc(msg_len); // buf should be aligned with 4
          if(buf != NULL) {
            rb_read(&recv_rb, buf, msg_len);
            msg = (stack_msg_t *) buf;
            msg_recv_handler(msg);
            mem_free(buf);
          }

        }
        else {
          // packet flag mismatch
        }
      }
    }
  }
  return 0;
}

int32_t transport_ready_to_write() {
  if(handle < 0)
    return -1;
  // check command queue, send if any command in queue.
  transport_trigger_write();
  return 0;
}

static int32_t push_msg_to_send_buf(stack_msg_t *msg)
{
  int16_t msg_buf_len = msg->length + sizeof(stack_msg_t) + 1;
  char packet_head = FIXED_PACKET_HEAD;

  if(rb_available_space(&send_rb) > msg_buf_len)
  {
    rb_write(&send_rb, &packet_head, 1);
    rb_write(&send_rb, (char *)msg, msg_buf_len-1);
  }
  return 0;
}

int32_t transport_enqueue_msg(stack_msg_t *msg) {
  return enqueue_tail(&msg_queue, &msg);
}

int32_t transport_trigger_write()
{
  int16_t remain_num;
  stack_msg_t *msg = get_queue_head(&msg_queue);

  // queue -> ringbuffer
  while(msg!=NULL)
  {
    if(push_msg_to_send_buf(msg) == 0)
    {
      // successful send to send_buffer
      dequeue_head_pointer(&msg_queue);
      msg_free_buffer(msg);
    }
    else
    {
      // insufficient send_rb space
      break;
    }
    msg = (stack_msg_t *)get_queue_head(&msg_queue);
  }

  // ringbuffer -> serial port
  remain_num = rb_remaining_data(&send_rb);
  while(remain_num > 0)
  {
    int16_t srd_n = (remain_num>SERIAL_SINGLE_RW_LEN?SERIAL_SINGLE_RW_LEN:remain_num);
    char *buf = mem_alloc(srd_n);

    if(rb_read_prepare(&send_rb, buf, srd_n) == 0)
    {
      int32_t num = serial_write(handle, buf, srd_n);
      if(num > 0)
      {
        if(num < srd_n) {
          // write buffer in kernel may be full
          // should wait for fd notify
          // it was handled in serial.c
          break;
        }

        if(rb_read_commit(&send_rb, num) < 0){
          dbg_printf("read commit failed!");
        }
      }
      else {
        // write fail
        break;
      }
    }
    mem_free(buf);
    remain_num = rb_remaining_data(&send_rb);
  }

  return 0;
}

int32_t transport_buff_init()
{
  recv_buff = (char *)mem_alloc(RECV_BUFF_SIZE);
  send_buff = (char *)mem_alloc(SEND_BUFF_SIZE);
  if((!recv_buff) || (!send_buff)) {
    dbg_printf("malloc buff failed!");
    return -1;
  }

  ringbuffer_init(&recv_rb, recv_buff, RECV_BUFF_SIZE);
  ringbuffer_init(&send_rb, send_buff, SEND_BUFF_SIZE);

  queue_init(&msg_queue, msg_queue_buffer, MSG_QUEUE_SIZE);

  return 0;
}

int32_t transport_deinit()
{
  // TODO
  return 0;
}

int32_t transport_start(int16_t port, uint32_t baudrate, console_cmd_handler_t cmd_handler)
{
  //sprintf(str_fd, "/dev/ttyS%d", port);
  handle = serial_open(port);
  if(handle < 0)
  {
      dbg_printf("open com port error!(%d)", handle);
      return handle;
  }

  serial_setup(handle, baudrate);
  serial_purge_rx(handle);
  if(handle)
    serial_start(handle, transport_ready_to_read, transport_ready_to_write, cmd_handler);
  return 0;
}

int32_t transport_stop()
{
  int32_t ret=0;
  if(handle>0) {
    serial_purge_rx(handle);
    ret = serial_close(handle);
  }
  return ret;
}

int32_t transport_start_for_download(int16_t port, uint32_t baudrate)
{
  //sprintf(str_fd, "/dev/ttyS%d", port);
  handle = serial_open(port);
  if(handle < 0)
  {
      dbg_printf("open com port error!(%d)", handle);
      return handle;
  }

  serial_setup(handle, baudrate);
  serial_purge_rx(handle);
  
  return 0;
}

int32_t transport_write_poll(uint16_t port, uint32_t baudrate, char *buff, int32_t len, int32_t timeout_ms) {
  //int32_t s_hdl;
  int32_t remain = len;
  uint32_t t1 = os_get_time();

  if(handle<=0)
    return -1;
  
  while(remain > 0) {
    int32_t wr_n = serial_write(handle, buff+(len-remain), remain);
    if(wr_n < 0) {
     /*
      serial_close(s_hdl);
      return -2;
      */
    }
    else if(wr_n > 0) {
      remain -= wr_n;
      dbg_printf("writep:%d/%d\n", wr_n, remain);
    }

    if(os_get_duration_ms(t1) > timeout_ms) {
      //serial_close(s_hdl);
      return -3;
    }
    if(wr_n == 0) {
      os_sleep(20);
      serial_notify_write();
    }
  }
  
  //serial_close(s_hdl);
  return 0;
}

int32_t transport_read_poll(uint16_t port, uint32_t baudrate, char *buff, int32_t len, int32_t timeout_ms) {
  //int32_t s_hdl;
  int32_t remain = len;
  uint32_t t1 = os_get_time();
  uint16_t i;
  int32_t count;
  
  if(handle<=0)
    return -1;
  
  while(remain > 0) {
    int32_t rd_n=0;
    if((count=serial_get_rx_count(handle)) > 0) {
      rd_n = serial_read(handle, buff+(len-remain), remain);
      if(rd_n < 0) {
        /*
         serial_close(s_hdl);
         s_hdl = serial_open(port);
         if(s_hdl<=0)
           return -2;
         */
      }
      else if(rd_n > 0) {
        remain -= rd_n;
        dbg_printf("readp:[%d/%d]", rd_n, remain);
        for(i=rd_n;i>0;i--)
          dbg_printf("%x-", buff[len-remain-i]);
        dbg_printf("\n");
      }
    }

    if(os_get_duration_ms(t1) > timeout_ms) {
      //serial_close(s_hdl);
      return -3;
    }
    if(count == 0)
      os_sleep(10);
  }

  //serial_close(s_hdl);
  return 0;
}

int32_t transport_purge_rx(uint16_t port) {
  int32_t s_hdl;
  int32_t ret;
  
  if(handle>0) {
    ret = serial_purge_rx(handle);
  } else {
    s_hdl = serial_open(port);
    ret = serial_purge_rx(s_hdl);
    serial_close(s_hdl);
  }
  return ret;
}


