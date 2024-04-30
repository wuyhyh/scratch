//编写一个程序统计行数、单词数、字符数
//我们用一个state变量来判断我们是否处于一个单词内，初始在单词外

#include <stdio.h>
#define OUT 0
#define IN 1

int main()
{
	int state = OUT;
	int c;
	int nline = 0;
	int nword = 0;
	int nchar = 0;

	while ((c = getchar()) != EOF) {
		nchar++; //每一次读取字符+1
		if (c == '\n') //换行符个数就是行数
			nline++;
		if (c == ' ' || c == '\n' || c == '\t') //确定是不是在单词外
			state = OUT;
		else if (state == OUT) { //如果之前都不是空字符，那么就进入了单词内
			state = IN; //避免单词内重复计数
			nword++;
		}
	}

	printf("nline = %d,nword = %d,nchar = %d\n", nline, nword, nchar);

	return 0;
}
