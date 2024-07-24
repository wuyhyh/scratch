/******************************************************************************
 *
 * Name: hello.c - 打印进程ID
 * Created on 2024/05/26
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "../include/apue.h"

int main(int argc, char argv[])
{
	printf("hello from process ID %ld\n", (long)getpid());
	exit(0)
}
