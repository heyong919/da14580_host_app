#include "ringbuffer.h"
#include "serial.h"

int32_t transport_init(int16_t port);
int32_t transport_start(console_cmd_handler_t cmd_handler);
int32_t transport_trigger_write(void);
