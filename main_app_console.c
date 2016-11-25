/*
 ============================================================================
 Name        : da14580_host_app.c
 Author      : hey
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */
#ifdef APP_ON_CONSOLE

#include <stdio.h>
#include <stdlib.h>
#include "co_error.h"
#include "app_msg.h"
#include "app_api.h"
#include "profiles.h"
#include "transport.h"
#include "binary.h"

extern int32_t da14580_boot_code(int16_t port, uint32_t baudrate, char *code, uint32_t len, char crc);
extern int32_t da14580_init(int16_t port);

static char calc_code_crc(char *code_buff, uint32_t len)
{
  char res=0;
  char *temp = code_buff;
  uint32_t i;

  for(i=0;i<len;i++) {
    res = (res^(*temp));
    temp++;
  }
  return res;
}

int main(int argc, char *argv[]) {
  int16_t com_num=0;
  char crc;
  int32_t ret;
  
  if(argc <2)
    com_num = 12;
  else
    com_num = atoi(argv[1]);

  crc = calc_code_crc(raw_code, sizeof(raw_code));
  dbg_printf("ble_firmware_download crc:%x\n", crc);
  ret = da14580_boot_code(com_num, 57600, raw_code, sizeof(raw_code), crc);
  if(ret<0)
    return EXIT_SUCCESS;


  da14580_init(com_num);
  
  return EXIT_SUCCESS;
}
#endif
