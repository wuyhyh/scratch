/******************************************************************************
 *
 * Name: getcputc.c - 使用标准I/O将标准输入复制到标准输出
 * Created on 2024/05/26
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "apue.h"

int main(int argc, char *argv[])
{
	int c; // char variable
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
