/******************************************************************************
 *
 * Name: client.c - Description
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

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE];
	FILE *file;
	ssize_t bytes_read;

	// 检查命令行参数，确保提供了文件名和服务器 IP
	if (argc != 3) {
		printf("用法：%s <服务器IP地址> <文件路径>\n", argv[0]);
		return -1;
	}

	const char *server_ip = argv[1]; // 服务器 IP 地址
	const char *file_path = argv[2]; // 要发送的文件路径

	// 1. 创建套接字
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("套接字创建失败");
		return -1;
	}

	// 2. 设置服务器地址和端口
	serv_addr.sin_family = AF_INET; // 使用 IPv4 地址族
	serv_addr.sin_port = htons(PORT); // 端口号，使用 htons 转换为网络字节序

	// 将 IP 地址从文本转换为二进制形式
	if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
		printf("无效的地址/地址不支持：%s\n", server_ip);
		close(sock);
		return -1;
	}

	// 3. 连接到服务器
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
	    0) {
		perror("连接失败");
		close(sock);
		return -1;
	}
	printf("已连接到服务器 %s:%d。\n", server_ip, PORT);

	// 4. 打开要发送的文件
	file = fopen(file_path, "r");
	if (file == NULL) {
		perror("无法打开文件");
		close(sock);
		return -1;
	}

	printf("正在发送文件 '%s'...\n", file_path);

	// 5. 读取文件内容并发送
	while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) >
	       0) {
		if (send(sock, buffer, bytes_read, 0) < 0) {
			perror("发送失败");
			fclose(file);
			close(sock);
			return -1;
		}
	}

	printf("文件发送完成。\n");

	// 6. 关闭文件和套接字
	fclose(file);
	close(sock);

	return 0;
}
