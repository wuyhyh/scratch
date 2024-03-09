//行计数
//标准库保证输入的每一行都以'\n'作为结尾，因此\
只需要统计换行符的个数就能统计行数

#include <stdio.h>

int main()
{
	int count = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n')
			count++;
	}
	printf("%d\n", count);

	return 0;
}
