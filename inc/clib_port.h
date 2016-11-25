/*
 * clib_port.h
 *
 *  Created on: 2016/11/21
 *      Author: heyong
 */

#ifndef INC_CLIB_PORT_H_
#define INC_CLIB_PORT_H_

#if defined(APP_ON_CONSOLE)

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define dbg_printf(format, ...)  printf(format, ##__VA_ARGS__)

#elif defined(APP_ON_MTK_NUCLEUS)

#include "kal_general_types.h"
#include "kal_public_api.h"
#include "kal_trace.h"

typedef kal_uint32 uint32_t;
typedef kal_uint16 uint16_t;
typedef kal_uint8 uint8_t;
typedef kal_int32 int32_t;
typedef kal_int16 int16_t;
typedef kal_int8 int8_t;

#define dbg_printf(...)  kal_prompt_trace(MOD_BLE, __VA_ARGS__)

#else
#endif

#ifndef bool
#define bool char
#define true 1
#define false 0
#endif

void os_sleep(uint32_t ms);
uint32_t os_get_time();
uint32_t os_get_duration_ms(uint32_t prev);
void* mem_alloc (uint32_t size);
void mem_free (void *p);

#endif /* INC_CLIB_PORT_H_ */
