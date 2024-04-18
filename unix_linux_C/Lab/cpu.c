//
// Created on 4/18/24.
//

// 循环打印代码
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "common.h" // 在编译的时候要指定gcc标志 -I ./include 到指定的目录搜索头文件

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: cpu <string>.\n");
		exit(1);
	}
	char *str = argv[1];
	while (1) {
		spin_(1);
		printf("%s\n", str);
	}
	return 0;
}
