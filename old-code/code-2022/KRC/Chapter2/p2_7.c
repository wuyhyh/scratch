//类型转换

//char类型可以存储较小的整数，我们编写一个程序将字符串转化为整数

#include <stdio.h>

int atoi(char s[])
{
	int n = 0;
	int i;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
		n = 10 * n + (s[i] - '0'); //确实很巧妙，我想不到
	}
	return n;
}

//编写一个大写字母转小写字母的程序
//在一个字符集中，A-Za-z都是连续的

int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A'); //加上一个固定的间隔
	else
		return c;
}

int main()
{
	char s[] = "1234";
	printf("%d\n", atoi(s));
	int c = 'S';
	putchar(lower(c));

	return 0;
}
