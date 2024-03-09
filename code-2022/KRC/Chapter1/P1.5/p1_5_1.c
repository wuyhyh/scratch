//标准库提供的输入输出模型：将所有输入输出都看成字符流\
文本流是多行字符构成的字符序列\
每行字符由0个或多个字符构成，行末是一个换行符

//使用c=getchar() putchar()可以在不了解输入输出知识的情况下\
编写出数量惊人的有用代码

//文件复制最基本的思路就是把输入的一次一个字符地复制到输出

#include <stdio.h>

void more_compress()
{
	int c;

	while ((c = getchar()) != EOF) { //更紧凑的写法
		putchar(c);
	}
}

int main()
{
	int c;

	c = getchar();
	while (c != EOF) { //EOF是一个整数
		putchar(c);
		c = getchar();
	}

	//more_compress();

	return 0;
}
