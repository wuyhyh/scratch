//使用公式对华氏温度进行转换

#include <stdio.h>

int main()
{
	int lower = 0;
	int upper = 300;
	int step = 20;

	int fahr;
	int celsius;

	fahr = lower;
	while (fahr <= 300) {
		celsius = 5 * (fahr - 32) / 9; //如果直接使用5/9，会得到0
		printf("%d\t%d\n", fahr, celsius);
		fahr += step;
	}

	return 0;
}
