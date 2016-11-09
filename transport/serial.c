/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Yasir Khan
 * Email: yasir_electronics@yahoo.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "serial.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "stdtypes.h"

static struct fd_set fd_rd, fd_wr;
static uint8_t write_available=0;

int32_t serial_setup(int32_t fd, int32_t baudrate)
{
  struct termios serial_config;
  /* zeroize configuration */
  memset(&serial_config, 0, sizeof(serial_config));
  /* get current serial attr */
  if (tcgetattr(fd, &serial_config)) {
    printf("Unable to get serial attributes: %s\r\n", strerror(errno));
    close(fd);
    return -ENODEV;
  }
  else {
    /*
     * Option.c_cflag &= ~PARENB; // no parity
     * Option.c_cflag &= ~CSTOPB; // 1 stop bit
     * Option.c_cflag &= ~CSIZE; // bit mask for data bits config
     * Option.c_cflag |= ~CS8;  // 8 data bits
     */
    tcflush(fd, TCIOFLUSH);
    //serial_config.c_iflag &= ~(INLCR | ICRNL);
    //serial_config.c_iflag |= IGNPAR | IGNBRK;
    //serial_config.c_oflag &= ~(OPOST | ONLCR | OCRNL);

    // set parity/stop bits/data bits, disable HW flow control
    serial_config.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS);
    serial_config.c_cflag |= CLOCAL | CREAD | CS8;
    // set for raw data transfer
    serial_config.c_lflag &= ~(ICANON | ISIG | ECHO | ECHOE);
    /* Set the desired baudrate */
    cfsetispeed(&serial_config, baudrate);
    cfsetospeed(&serial_config, baudrate);
    /* data wait time-out */
    //serial_config.c_cc[VTIME] = 1;
    /* Minimum data bytes available before read is successful */
    //serial_config.c_cc[VMIN] = 0;
    /* set attributes */
    if (tcsetattr(fd, TCSANOW, &serial_config)) {
      printf("Unable to set serial attributes: %s\r\n", strerror(errno));
      close(fd);
    }
  }
  return 0;
}

int32_t serial_start(int32_t fd, ready_to_read_callback_t read_cb, ready_to_write_callback_t write_cb)
{
  int32_t result;
  struct timeval tv;

  FD_ZERO(&fd_rd);
  FD_ZERO(&fd_wr);
  FD_SET(fd, &fd_rd);
  FD_SET(fd, &fd_wr);
  tv.tv_sec = 1;
  tv.tv_usec = 0;

  while(1){
    FD_SET(0, &fd_rd);
    if(write_available == 0)
      FD_SET(fd, &fd_wr);
    FD_SET(fd, &fd_rd);
    result = select(fd+1, &fd_rd, &fd_wr, NULL, &tv);
    if(result == 0) { // timeout
      //printf("select timeout\n");
    }
    else if(result < 0) {
      printf("select failed %d\n", result);
    }
    else {
      if(FD_ISSET(fd, &fd_rd)) {
        //printf("read avail\n");
        //nread=read(fd, buff, 16);
        read_cb(fd);
        FD_SET(fd, &fd_rd);
      }
      if(FD_ISSET(fd, &fd_wr)) {
        //nwrriten = write(fd, buff, 10);
        //printf("write length=%d\n", nwrriten);
        write_available = 1;
        write_cb(fd);
        FD_CLR(fd, &fd_wr);
      }
      if(FD_ISSET(0, &fd_rd)) {
        char buf[36];
        int32_t nrd;
        nrd=read(0, buf, 32);
        buf[nrd]='\0';
        printf("std input[%d]: %s\n", nrd, buf);
      }
    }
  }
}

int32_t serial_write(int32_t fd, char *data, uint16_t length)
{
  int32_t ret;

  ret = write(fd, data, length);
  if (ret < 0) {
    printf("Unable to write serial: %s\r\n", strerror(errno));
  }
  return ret;
}

int32_t serial_read(int32_t fd, const char *buff, int32_t len)
{
  int32_t ret;

  ret = read(fd, buff, len);
  if (ret < 0) {
    printf("Unable to read serial: %s\r\n", strerror(errno));
  }
  return ret;
}
/* open the serial device, make sure it is not being used by any other program */
int32_t serial_open(const char *name)
{
  int32_t serial_fd = open(name, O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (serial_fd < 0) {
    printf("Unable to open serial device: %s: %s \r\n", name, strerror(errno));
  }
  return serial_fd;
}

int32_t serial_close(int32_t fd)
{
}
