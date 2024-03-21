//
// Created by wyh on 2024/1/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

// fork和exec搭配使用

// 使用重定向技术，打开文件
/**/
int main(int argc, char *argv[])
{
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed.\n");
		exit(1);
	} else if (rc == 0) {
		close(STDOUT_FILENO);
		open("../src/ostep/chapter5/p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

		char *myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("../src/ostep/chapter5/p4.c");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
	} else {
		int wc = wait(NULL); // 使用wait系统调用，保证parent等待child执行完成
	}

	return 0;
}