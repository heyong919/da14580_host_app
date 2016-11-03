/*
 * uart.c
 *
 *  Created on: 2016Äê11ÔÂ1ÈÕ
 *      Author: heyong
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <termios.h>
#include <errno.h>
#include "stdtypes.h"

int32_t comfd=-1;

int32_t uart_init(uint8_t id, uint32_t baudrate)
{
	//struct termios Opt;
	char str_fd[32];

	sprintf(str_fd, "/dev/ttyS%d", id);
	comfd = open(str_fd, O_RDWR);
	if(-1 == comfd)
	{
	    printf("open com(%d) error!", id);
	    return -EFAULT;
	}


	//tcgetattr(comfd);
	//cfsetispeed(&Opt, 115200);
	//cfsetospeed(&Opt, 115200);
	//tcsetattr(comfd, TCANOW, &Opt);
}

