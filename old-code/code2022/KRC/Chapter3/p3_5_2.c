#include <stdio.h>
#include <string.h>

void reverse(char ss[])
{
	int len = strlen(ss);

	for (int i = 0, j = len - 1; i < j; i++, j--) {
		char c;
		c = ss[i], ss[i] = ss[j],
		ss[j] = c; //使用逗号运算符，这样可以看作one step
	}
}

int main()
{
	char ss[] = "wuyuhang";
	printf("%s\n", ss);
	reverse(ss);
	printf("%s\n", ss);

	return 0;
}
