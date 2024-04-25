//字符计数。与文件复制的原理类似

#include <stdio.h>

int while_ed() //while版本
{
	int c;
	int count = 0;
	while ((c = getchar()) != EOF) {
		count++;
	}
	return count;
}

int for_ed()
{
	int c;
	int count = 0;
	for (; (c = getchar()) != EOF; count++) //for循环每个部分都可以省略
		; //这是一个空语句
	return count;
}

int main()
{
	//printf("%d\n", while_ed());
	printf("%d\n", for_ed());
}
//while和for循环在开始的地方进行条件测试，有利于处理长度为0的情况\
确保程序执行合理的操作
