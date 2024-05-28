/******************************************************************************
 *
 * Name: testerror.c - 出错函数的使用方法
 * Created on 2024/05/26
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "apue.h"
#include <error.h>

int main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);

	exit(0);
}
