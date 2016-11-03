/*
 ============================================================================
 Name        : da14580_host_app.c
 Author      : hey
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "app_api.h"

int main(void) {
	printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */

    uart_init(35, 115200);


	return EXIT_SUCCESS;
}
