# Makefile for building client and server programs

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -O2

# 目标可执行文件
TARGETS = client server

# 默认目标，编译所有目标
all: $(TARGETS)

# 生成 client 程序
client: client.c
	$(CC) $(CFLAGS) -o client client.c

# 生成 server 程序
server: server.c
	$(CC) $(CFLAGS) -o server server.c

# 清理生成的文件
clean:
	rm -f $(TARGETS)
	rm -f *.o

# 伪目标
.PHONY: all clean
