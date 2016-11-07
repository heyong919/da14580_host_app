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
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int serial_dev;
	int ret;
	char data[256];

	if (argc < 2) {
		fprintf(stderr, "Please specify serial device to use \r\n");
		return -1;
	}
	
	printf("Serial device to open: %s \r\n", argv[1]);
	
	serial_dev = serial_open(argv[1]);
	if (serial_dev < 0) {
		fprintf(stderr, "Unable to open serial device: %s: %s\r\n", argv[1], strerror(errno));
		return -1;
	}
	
	if (serial_setup(serial_dev, 115200)) {
		fprintf(stderr, "Unable to setup serial device: %s: %s\r\n", argv[1], strerror(errno));
	}

	while (1) {
		serial_write(serial_dev, "Testing");
		ret = serial_read(serial_dev, data, sizeof(data));
		if (ret <= 0) {
			printf("No data available \r\n");
		} else {
			printf("Serial data received:\r\n");
			printf("%s\r\n", data);
		}
		sleep(1);
	}
}
