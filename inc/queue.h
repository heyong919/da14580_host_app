/*
 * queue.h
 *
 *  Created on: 2016Äê11ÔÂ15ÈÕ
 *      Author: heyong
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_


#define QUEUE_TYPE  stack_msg_t*
#define QUEUE_SIZE  16

void queue_init();
int16_t enqueue_tail(QUEUE_TYPE p);
int16_t enqueue_head(QUEUE_TYPE p);
QUEUE_TYPE get_queue_head();
void dequeue_head_pointer();
QUEUE_TYPE dequeue();

#endif /* INC_QUEUE_H_ */
