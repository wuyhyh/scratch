//c语言中函数是通过传值就行调用参数的\
函数只处理参数的副本，并不修改原来的变量
//如果想要修改变量，那么就要传递变量的地址
//对于数组名来说，数组名是一个地址

#include <stdio.h>

int power(int base, int n)
{
	int po = 1;
	for (int i = 1; i <= n; i++) {
		po *= base;
	}
	return po;
}

int main()
{
	printf("pow(2,10) = %d\n", power(2, 10));
	return 0;
}
