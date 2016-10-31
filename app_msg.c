/*
 * app_msg.c
 *
 *  Created on: 2016Äê10ÔÂ31ÈÕ
 *      Author: heyong
 */

#include "app_msg.h"

stack_msg_t* msg_alloc_buffer(uint16_t paralen)
{
	uint8_t *buffer = malloc(8+paralen);
	return (stack_msg_t *)buffer;
}

int msg_fill(stack_msg_t *msg_buf, uint16_t type, uint16_t srcid, uint16_t dstid, uint16_t paralen, uint8_t *param)
{
	msg_buf->length = paralen;
	if(paralen)
		memcpy(msg_buf->data, param, paralen);
	msg_buf->type = type;
	msg_buf->src_id = srcid;
	msg_buf->dst_id = dstid;

	return 0;
}

int msg_send(stack_msg_t *msg)
{
	//return uart_enqueue(msg);
}

