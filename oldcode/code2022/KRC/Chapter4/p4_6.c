#include <stdio.h>

int ss(int i)
{
	static int st; //不进行显式初始化自动初始化为0
	st += i;
	return st;
}

int main()
{
	printf("%d\n", ss(20)); //只有一个实例
	printf("%d\n", ss(20));
	printf("%d\n", ss(20));
	register int a = 20;
	printf("%d\n", a);
	return 0;
}
