#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "stdtypes.h"
#include "app_msg.h"
#include "queue.h"
#include "transport.h"

#define SEND_BUFF_SIZE  (1024)
#define RECV_BUFF_SIZE  (1024)

#define SERIAL_SINGLE_RW_LEN  128

static char *recv_buff;
static char *send_buff;
//static int16_t recv_r, recv_w, send_r, send_w;
static ringbuffer_t send_rb, recv_rb;
int32_t port_fd=-1;


static int32_t uart_ready_to_read(int32_t fd) {
  int32_t rd_num, buf_size;
  char *buf;
  char packet_head[sizeof(stack_msg_t)+1]; // 9 bytes
  stack_msg_t *msg;

  buf = malloc(SERIAL_SINGLE_RW_LEN);
  buf_size = rb_available_space(&recv_rb);
  while(buf_size > 0) {
    if(buf_size > SERIAL_SINGLE_RW_LEN)
      buf_size = SERIAL_SINGLE_RW_LEN;

    rd_num = serial_read(fd, buf, buf_size);
    printf("read[%d]: %s\n", rd_num, recv_buff);

    if(rb_write(&recv_rb, buf, rd_num) < 0)
      printf("rb_write failed!\n");
    if(rd_num < buf_size)
      break;

    buf_size = rb_available_space(&recv_rb);
  }
  free(buf);

  while(rb_remaining_data(&recv_rb) > sizeof(packet_head)) {
    if(rb_read_prepare(&recv_rb, packet_head, sizeof(packet_head)) == 0) {
      if(packet_head[0] == FIXED_PACKET_HEAD) {
        // msg_len exclude packet header
        // this is to ensure message data aligned
        int32_t msg_len = sizeof(stack_msg_t) + packet_head[7] + (packet_head[8]<<8);
        if(rb_remaining_data(&recv_rb) >= msg_len) {
          rb_read_commit(&recv_rb, 1); // skip packet header
          buf = malloc(msg_len); // buf should be aligned with 4
          if(buf != NULL) {
            rb_read(&recv_rb, buf, msg_len);
            msg = (stack_msg_t *) buf;
            msg_recv_handler(msg);
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

static int32_t uart_ready_to_write(int32_t fd) {
  // check command queue, send if any command in queue.
  return 0;
}

static int32_t push_msg_to_send_buf(stack_msg_t *msg)
{
  int16_t msg_buf_len = msg->length + sizeof(stack_msg_t);

  if(rb_available_space(&send_rb) > msg_buf_len)
  {
    rb_write(&send_rb, (char *)msg, msg_buf_len);
  }
  return 0;
}

int32_t transport_trigger_write()
{
  int16_t remain_num;
  stack_msg_t *msg = get_queue_head();

  while(msg!=NULL)
  {
    if(push_msg_to_send_buf(msg) == 0)
    {
      // successful send to send_buffer
      dequeue_head_pointer();
    }
    else
    {
      // insufficient send_buff
      break;
    }
    msg = (stack_msg_t *)(uint64_t)get_queue_head();
  }

  remain_num = rb_remaining_data(&send_rb);
  while(remain_num > 0)
  {
    int16_t srd_n = (remain_num>SERIAL_SINGLE_RW_LEN?SERIAL_SINGLE_RW_LEN:remain_num);
    char *buf = malloc(srd_n);

    if(rb_read_prepare(&send_rb, buf, srd_n) == 0)
    {
      int32_t num = serial_write(port_fd, buf, srd_n);
      if(num > 0)
      {
        if(num < srd_n) {
          // write buffer in kernel may be full
          // should wait for fd notify
          // it was handled in serial.c
          break;
        }

        if(rb_read_commit(&send_rb, num) < 0){
          printf("read commit failed!");
        }
      }
      else {
        // write fail
        break;
      }
    }
    remain_num = rb_remaining_data(&send_rb);
  }

  return 0;
}

int32_t transport_init(int16_t port)
{
	char str_fd[32];

  recv_buff = (char *)malloc(RECV_BUFF_SIZE);
  send_buff = (char *)malloc(SEND_BUFF_SIZE);
  if((!recv_buff) || (!send_buff)) {
    printf("malloc buff failed!");
    return -1;
  }

  ringbuffer_init(&recv_rb, recv_buff, RECV_BUFF_SIZE);
  ringbuffer_init(&send_rb, send_buff, SEND_BUFF_SIZE);

  queue_init();

	sprintf(str_fd, "/dev/ttyS%d", port);
  port_fd = serial_open(str_fd);
  if(-1 == port_fd)
	{
	    printf("open com port error!");
	    return -EFAULT;
	}

  serial_setup(port_fd, B115200);

  return 0;
}

int32_t transport_start(console_cmd_handler_t cmd_handler)
{
  if(port_fd)
    serial_start(port_fd, uart_ready_to_read, uart_ready_to_write, cmd_handler);
  return 0;
}

