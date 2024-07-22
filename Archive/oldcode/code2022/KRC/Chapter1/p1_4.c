//使用幻数不是一种好的方法，不利于修改和阅读
//我们用符号常量来赋予这些数字意义
//使用#define 做替换文本

#include <stdio.h>
#define UPPER 300
#define LOWER 0
#define STEP 20

int main()
{
	int fahr;
	for (fahr = LOWER; fahr <= UPPER; fahr += STEP) {
		printf("%3d\t%6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
	}

	return 0;
}
