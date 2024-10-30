/******************************************************************************
 *
 * Name: server.c - Description
 * Created on 2024/10/30
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	 // close() 函数
#include <arpa/inet.h>	 // 套接字函数及数据结构
#include <sys/socket.h>	 // 套接字函数及数据结构
#include <netinet/in.h>	 // 套接字地址结构

#define PORT 8080	 // 服务器监听的端口号
#define BUFFER_SIZE 1024 // 缓冲区大小

int main()
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	FILE *file;

	// 1. 创建套接字
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("套接字创建失败");
		exit(EXIT_FAILURE);
	}

	// 2. 绑定地址和端口
	address.sin_family = AF_INET;	      // 使用 IPv4 地址族
	address.sin_addr.s_addr = INADDR_ANY; // 接受任意 IP 地址的连接
	address.sin_port = htons(PORT); // 端口号，使用 htons 转换为网络字节序

	// 绑定套接字到指定地址和端口
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("绑定失败");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// 3. 开始监听
	if (listen(server_fd, 3) < 0) {
		perror("监听失败");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("服务器正在监听端口 %d...\n", PORT);

	// 4. 接受客户端连接
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
				 (socklen_t *)&addrlen)) < 0) {
		perror("接受连接失败");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("接受到来自客户端的连接。\n");

	// 5. 接收文件内容并保存
	file = fopen("received_file.txt", "w");
	if (file == NULL) {
		perror("无法创建文件");
		close(new_socket);
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("正在接收文件...\n");

	while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
		fwrite(buffer, sizeof(char), bytes_read, file);
	}

	printf("文件接收完成，保存为 'received_file.txt'。\n");

	// 6. 关闭文件和套接字
	fclose(file);
	close(new_socket);
	close(server_fd);

	return 0;
}
