// ls命令的实现

#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2)
		err_quit("usage is not a directory_name");

	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	while ((dir = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir();
	exit(0);
}