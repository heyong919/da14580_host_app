#include "ringbuffer.h"
#include "serial.h"
#include "app_msg.h"

int32_t transport_buff_init();
int32_t transport_deinit();
int32_t transport_start(int16_t port, uint32_t baudrate, console_cmd_handler_t cmd_handler);
int32_t transport_start_for_download(int16_t port, uint32_t baudrate);
int32_t transport_stop();
int32_t transport_trigger_write(void);
int32_t transport_enqueue_msg(stack_msg_t *msg);
// triggered from upper or lower layers
int32_t transport_ready_to_read();
int32_t transport_ready_to_write();
int32_t transport_write_poll(uint16_t port, uint32_t baudrate, char *buff, int32_t len, int32_t timeout_ms);
int32_t transport_read_poll(uint16_t port, uint32_t baudrate, char *buff, int32_t len, int32_t timeout_ms);
int32_t transport_purge_rx(uint16_t port);
