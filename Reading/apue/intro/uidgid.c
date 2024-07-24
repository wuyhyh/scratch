/******************************************************************************
 *
 * Name: uidgid.c - 用户标识
 * Created on 2024/05/27
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "../include/apue.h"

int main(int argc, char *argv[])
{
	printf("uid = %d,gid = %d\n", getuid(), getgid());
	exit(0);
}
