//使用浮点数使结果更精确，同时让输出右对齐更美观

#include <stdio.h>

int main()
{
	int lower = 0;
	int upper = 300;
	int step = 20;

	double fahr = lower;
	double celsius;

	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32); //这里是发生了类型转换的
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr += step;
	}

	return 0;
}
