#include<stdio.h>

int factorial(int n)
{
	if (n == 0)
		return 1;//��������
	else
		return n * factorial(n - 1);//��ϵʽ
}

int main()
{
	printf("4! = %d\n", factorial(4));
	return 0;
}