//函数内部的变量是局部变量，只在函数调用时存在
//static 修饰的局部变量在多次函数调用期间值不变
//外部变量定义在所有函数之外，只能定义一次，\
  在整个程序执行期间存在，并且值不会被调用函数改变
//每个需要使用外部变量的函数都需要在他的内部重新声明外部变量：在前面加个extern
//如果要使用的外部变量就在当前函数的前面，那么可以省略extern
//一种做法是把外部变量集中放在头文件中

//要谨慎区别定义和声明：\
定义是创建变量并分配存储单元；声明只说明变量的性质，不分配存储单元

//外部变量的使用方便了函数之间的通信，但是可能带来逻辑的混乱和难以发现的错误

#include <stdio.h>
#include "var_f.h"

int var = 100;

int change(int a)
{
	a += 10;
	return a;
}

int main()
{
	extern int var;
	printf("var = %d\n", var);
	change(var);
	printf("var = %d\n", var); //通过指针才能改变值

	extern double var_f;
	printf("var_f = %.2f\n", var_f);

	return 0;
}
