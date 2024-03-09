#include <stdio.h>
#include <ctype.h> //isdigit()

int atoi(char s[])
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); i++) //跳过空白符
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') //跳过sign
		i++;
	for (n = 0; isdigit(s[i]); i++) {
		n = 10 * n + (s[i] - '0');
	}
	return n * sign;
}

int main()
{
	char ss[] = "-123";
	printf("%d\n", atoi(ss));
	return 0;
}
