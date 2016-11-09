/*
 * queue.c
 *
 *  Created on: 2016/11/10
 *      Author: heyong
 */

#include "stdtypes.h"
#include "app_msg.h"

#define QUEUE_TYPE  stack_msg_t*
#define QUEUE_SIZE  16

static QUEUE_TYPE queue[QUEUE_SIZE];
static int16_t qhead, qtail;

#define queue_full() ((qtail+1)%QUEUE_SIZE == qhead)
#define queue_empty() (qhead == -1 && qtail == -1)

void queue_init()
{
  qhead = -1;
  qtail = -1;
}

int16_t enqueue_tail(QUEUE_TYPE p)
{
  if(queue_full())
    return -1;
  qtail = (qtail+1)%QUEUE_SIZE;
  queue[qtail] = p;
  if(qhead == -1)
  {
    qhead = qtail;
  }
  return 0;
}

int16_t enqueue_head(QUEUE_TYPE p)
{
  if(queue_full())
    return -1;
  qhead = (qhead-1+QUEUE_SIZE)%QUEUE_SIZE;
  queue[qhead] = p;
  if(qtail == -1)
  {
    qtail = qhead;
  }
  return 0;
}

QUEUE_TYPE dequeue()
{
  int16_t temp;
  if(queue_empty())
    return NULL;
  temp = qhead;
  if(qhead == qtail)
    qhead = qtail = -1;
  else
    qhead = (qhead+1)%QUEUE_SIZE;
  return queue[temp];
}

