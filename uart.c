#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "stdtypes.h"

#define MAX_READ_SIZE  (64)

static char *read_buff;
int32_t comfd=-1;

static int32_t uart_ready_to_read(int32_t fd) {
  int32_t rd_num;

  rd_num = serial_read(fd, read_buff, MAX_READ_SIZE);
  printf("read[%d]: %s\n", rd_num, read_buff);
  return 0;
}

static int32_t uart_ready_to_write(int32_t fd) {
  // check command queue, send if any command in queue.
  ;
}

int32_t uart_init(uint8_t id, uint32_t baudrate)
{
	//struct termios Opt;
	char str_fd[32];

  read_buff = (char *)malloc(MAX_READ_SIZE);
  if(!read_buff) {
    printf("malloc buff failed!");
    return -1;
  }

	sprintf(str_fd, "/dev/ttyS%d", id);
  comfd = serial_open(str_fd);
  if(-1 == comfd)
	{
	    printf("open com(%d) error!", id);
	    return -EFAULT;
	}

  serial_setup(comfd, B115200);

  serial_start(comfd, uart_ready_to_read, uart_ready_to_write);

}

