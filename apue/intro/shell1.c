/******************************************************************************
 *
 * Name: shell1.c - 进程控制函数fork(),从标准输入中读入命令并执行
 * Created on 2024/05/26
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% "); // print prompt here
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; // replace new line with null

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) { // child
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		// parent
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");

		printf("%% ");
	}

	exit(0);
}
