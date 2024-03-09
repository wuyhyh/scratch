#include <stdio.h>

void printd(int n) //只处理正数
{
	if (n / 10) {
		printd(n / 10);
	}
	putchar(n % 10 + '0');
	putchar(' ');
}

int main()
{
	int n = 1234;
	printd(n);

	return 0;
}
