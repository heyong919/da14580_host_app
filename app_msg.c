/*
 * app_msg.c
 *
 *  Created on: 2016Äê10ÔÂ31ÈÕ
 *      Author: heyong
 */

#include "app_msg.h"

stack_msg_t* msg_alloc_buffer(uint16_t paralen)
{
	uint8_t *buffer = malloc(sizeof(stack_msg_t)+paralen);
	return (stack_msg_t *)buffer;
}

void msg_free_buffer(stack_msg_t *msg_p)
{
  free(msg_p);
}

int32_t msg_fill(stack_msg_t *msg_buf, uint16_t type, uint16_t srcid, uint16_t dstid, uint16_t paralen, uint8_t *param)
{
	msg_buf->length = paralen;
	if(paralen)
		memcpy(msg_buf->data, param, paralen);
	msg_buf->type = type;
	msg_buf->src_id = srcid;
	msg_buf->dst_id = dstid;

	return 0;
}

int32_t msg_send(stack_msg_t *msg)
{
  int16_t result;
  result = enqueue_tail(msg);
  if(result < 0)
  {
    printf("enqueue failed, queue full!\n");
  }
}

