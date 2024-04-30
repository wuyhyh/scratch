//共用体的一个例子

#include<stdio.h>

int main()
{
	union exm{
		int i;
		char ch[2];
	}u;

	u.i = 258;
	printf("%d\t%d\n", u.ch[0], u.ch[1]);

	return 0;
}