//
// Created by root on 4/25/24.
//

// 列出一个目录中的所有文件
// 目录是什么？目录是包含目录项的文件，本质上还是文件。

#include "../include/apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2)
		err_quit("usage: is directory_name");

	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
