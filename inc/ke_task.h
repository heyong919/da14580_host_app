/**
 ****************************************************************************************
 *
 * @file ke_task.h
 *
 * @brief This file contains the definition related to kernel task management.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef _KE_TASK_H_
#define _KE_TASK_H_

/**
 ****************************************************************************************
 * @defgroup TASK Task and Process
 * @ingroup KERNEL
 * @brief Task management module.
 *
 * This module implements the functions used for managing tasks.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <compiler.h>        // compiler defines, INLINE
#include <stdint.h>          // standard integer
#include <stdbool.h>         // standard boolean

#include "rwip_config.h"     // stack configuration
#include "ke_msg.h"          // kernel message defines

/// Build the first message ID of a task.
#define KE_FIRST_MSG(task) ((ke_msg_id_t)((task) << 10))
#define MSG_T(msg)         ((ke_task_id_t)((msg) >> 10))
#define MSG_I(msg)         ((msg) & ((1<<10)-1))

/// @} TASK

#endif // _KE_TASK_H_

