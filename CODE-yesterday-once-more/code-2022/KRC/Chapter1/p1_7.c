//编写一个求x的n次幂的程序\
这个算法只适合比较小的幂\
标准库中有一个pow()函数

#include <stdio.h>

int pow(int x, int n)
{
	int power = 1;
	for (int i = 1; i <= n; i++) {
		power *= x;
	}
	return power;
}

int main(int argc, char **argv)
{
	int x = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("pow(%d,%d) = %d\n", x, n, pow(x, n));

	return 0;
}
//使用Ctrl+`召唤终端
