/******************************************************************************
 *
 * Name: seek.c - 测试标准输入能否设置偏移量
 * Created on 2024/06/02
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "apue.h"

int main()
{
	if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	exit(0);
}
