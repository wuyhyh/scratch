//编写一个程序，输出整数x中1的位有多少

#include <stdio.h>

int bits_count(unsigned x)
{
	int b = 0;

	for (int i = 0; x != 0; x >>= 1) {
		if (x & 01)
			b++;
	}
	return b;
}

int main()
{
	unsigned test_bits = 0b11011101;
	printf("%d\n", bits_count(test_bits));

	return 0;
}
