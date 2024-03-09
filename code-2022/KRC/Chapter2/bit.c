//位运算有6个 & | ~ ^ << >>

#include <stdio.h>
#include <stdlib.h>

int test_bit1 = 0b11011001; //0xd9
int test_bit2 = 0b10110101; //0xb5

void output_bin(int i)
{
	char string[64];
	itoa(i, string, 2); //将数字转换成字符串，关掉微软的安全检查
	printf("%s\n", string);
}

//连按两次ctrl会显示函数参数提示
int main()
{
	int and = test_bit1 & test_bit2;
	output_bin(test_bit1);
	output_bin(test_bit2);
	output_bin(and);
	putchar('\n');

	int or = test_bit1 | test_bit2;
	output_bin(test_bit1);
	output_bin(test_bit2);
	output_bin(or);
	putchar('\n');

	int negate = 0xff & (~test_bit1);
	output_bin(test_bit1);
	output_bin(negate);
	putchar('\n');

	int xor = test_bit1 ^ test_bit2;
	output_bin(test_bit1);
	output_bin(test_bit2);
	output_bin(xor);
	putchar('\n');

	return 0;
}
