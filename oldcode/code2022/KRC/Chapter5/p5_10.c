#include <stdio.h>

int main(int argc, char *argv[])
{
	//argv是一个指针数组，这里的操作时遍历这个数组，然后取出其指向的字符串
	while (--argc > 0) {
		printf("%s\n", *++argv);
	}

	return 0;
}
