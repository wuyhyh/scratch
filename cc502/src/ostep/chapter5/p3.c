//
// Created by wyh on 2024/1/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// fork和exec搭配使用

int main(int argc, char *argv[])
{
	printf("hello world (pid:%d)\n", (int)getpid());

	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed.\n");
		exit(1);
	} else if (rc == 0) {
		printf("hello, I am child (pid:%d)\n", (int)getpid());
		char *myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("../src/ostep/chapter5/p3.c");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
		printf("this shouldn't print out.\n");
	} else {
		int wc = wait(NULL); // 使用wait系统调用，保证parent等待child执行完成
		printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc,
			   (int)getpid());
	}

	return 0;
}