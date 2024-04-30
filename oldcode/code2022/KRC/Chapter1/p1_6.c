//编写一个程序来统计0~9各个数字的出现次数，以及行数、空白字符数、其他字符数
//所有的字符分为三类，用一个数组ndigit[]来表示数字的个数是方便的

#include <stdio.h>

int main()
{
	int c;
	int ndigit[10] = { 0 };
	int nwhite = 0;
	int nother = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t')
			nwhite++;
		else if (c >= '0' && c <= '9') { //判断是否为数字
			ndigit[c - '0']++;
			//这里使用偏移量来计数很巧妙c-'0'是数字对应的数值
		} else {
			nother++;
		}
	}

	printf("nwhite = %d,nother = %d\n", nwhite, nother);
	for (int i = 0; i <= 9; i++) {
		printf("%d \n", ndigit[i]);
	}

	return 0;
}
