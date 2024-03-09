//&运算常用于屏蔽某些位，|运算用于把某些位置为1

//编写一个函数getbits(x,p,n)，从整数x中取出其右边第p位右侧的n位

#include <stdio.h>
#include <stdlib.h>

unsigned getbits(unsigned x, int p, int n)
{
	x >>= (p + 1 - n);
	x &= ~(~0 << n);
	return x;
}

void output_bin(unsigned i)
{
	char string[64];
	itoa(i, string, 2);
	printf("%s\n", string);
}

int main()
{
	unsigned test_bits = 0b11011101;
	output_bin(test_bits);
	unsigned r = getbits(test_bits, 4, 3);
	output_bin(r);

	return 0;
}
