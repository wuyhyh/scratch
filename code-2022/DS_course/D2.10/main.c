#include<stdio.h>

int factorial(int n)
{
	if (n == 0)
		return 1;//结束条件
	else
		return n * factorial(n - 1);//关系式
}

int main()
{
	printf("4! = %d\n", factorial(4));
	return 0;
}