/******************************************************************************
 *
 * Name: scull_test.c - Description
 * Created on 2024/08/04
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcnt.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_NAME " /dev/scull0"

void error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int main()
{
	int fd;
	char write_buf[] = "Hello, scull!";
	char read_buf[100];

	// 打开设备文件
	fd = open(DEVICE_NAME, O_RDWR);
	if (fd == -1) {
		error_exit("Failed to open device file");
	}

	// 写入数据
	if (write(fd, write_buf, strlen(write_buf)) == -1) {
		error_exit("Failed to write to the device");
	}
	printf("Data written to the device: %s\n", write_buf);

	// 设置文件偏移量到文件开头
	if (lseek(fd, 0, SEEK_SET) == -1) {
		error_exit("Failed to set file offset");
	}

	// 读取数据
	ssize_t read_bytes = read(fd, read_buf, sizeof(read_buf) - 1);
	if (read_bytes == -1) {
		error_exit("Failed to read from the device");
	}

	// 添加字符串终止符
	read_buf[read_bytes] = '\0';
	printf("Data read from the device: %s\n", read_buf);

	// 关闭设备文件
	if (close(fd) == -1) {
		error_exit("Failed to close the device file");
	}

	return 0;
}
