/******************************************************************************
 *
 * Name: forkxy.c - Description
 * Created on 2024/08/13
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t x = fork();
	pid_t y = fork();
	printf("%d %d\n", x, y);


	return 0;
}
