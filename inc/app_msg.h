/*
 * app_msg.h
 *
 *  Created on: 2016Äê10ÔÂ31ÈÕ
 *      Author: heyong
 */

#ifndef INC_APP_MSG_H_
#define INC_APP_MSG_H_

#include "stdtypes.h"
//#include "string.h"
#include "stdlib.h"
#include "compiler.h"
#include "profiles.h"

#define FIXED_PACKET_HEAD  (0x5)

// be carefull the alignment of struct:
// the element of the struct must have no padding.
typedef struct stack_msg
{
	uint16_t type;
	uint16_t dst_id;
	uint16_t src_id;
	uint16_t length;
	uint8_t data[__ARRAY_EMPTY];
} stack_msg_t;

#define MSG_GET_LENGTH(msg_p) (sizeof(stack_msg_t)+(msg_p)->length)

stack_msg_t* msg_alloc_buffer(uint16_t paralen);
int32_t msg_fill(stack_msg_t *msg_buf,
                 uint16_t type,
                 uint16_t srcid,
                 uint16_t dstid,
                 uint16_t paralen,
                 uint8_t *param);
int32_t msg_send(stack_msg_t *msg);
int32_t msg_recv_handler(stack_msg_t *msg);
void msg_free_buffer(stack_msg_t *msg_p);


#endif /* INC_APP_MSG_H_ */
