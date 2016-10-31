/**
 ****************************************************************************************
 *
 * @file ke_msg.h
 *
 * @brief This file contains the definition related to message scheduling.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef _KE_MSG_H_
#define _KE_MSG_H_

/**
 ****************************************************************************************
 * @defgroup MSG Message Exchange
 * @ingroup KERNEL
 * @brief Message scheduling module.
 *
 * The MSG module implements message scheduling functions.

 * A kernel message has an ID, a receiver task ID and a source task ID.
 * In most cases, it also has parameters which are defined in
 * a structure dynamically embedded in the message structure,
 * so the whole message will be managed internally as one block.
 *
 * A message can also have one extra parameter which is referenced
 * in the normal parameter structure. This extra block is assumed
 * to be large by the kernel and will be moved by DMA if needed.
 * This feature allows moving MMPDU from LMAC to UMAC.
 *
 * In order to send a message, a function first have to allocate
 * the memory for this message. It can be done with the wrapper
 * macro KE_MSG_ALLOC() (which will call ke_msg_alloc()).

 * The message can then be sent with ke_msg_send(). The kernel
 * will take care of freeing the allocated memory.

 * If the message has no parameters, the ke_msg_send_basic() function
 * can be used.
 *
 * @{
 ****************************************************************************************
 */

#include <stddef.h>          // standard definition
#include <stdint.h>          // standard integer
#include <stdbool.h>         // standard boolean

/// Task Identifier. Composed by the task type and the task index.
typedef uint16_t ke_task_id_t;

/// Task State
typedef uint8_t ke_state_t;

/// Message Identifier. The number of messages is limited to 0xFFFF.
/// The message ID is divided in two parts:
/// - bits[15..10] : task index (no more than 64 tasks supported).
/// - bits[9..0] : message index (no more that 1024 messages per task).
typedef uint16_t ke_msg_id_t;

/// @} MSG

#endif // _KE_MSG_H_
