//计算多项式在某一处的值

#include<stdio.h>
#include<time.h>
#include<math.h>//pow()

clock_t start;
clock_t stop;
double duration;

#define MAXN 10//最多处理9阶多项式，有10项

double fun(int n, double a[], double x);//蛮力算法
double qin(int n, double a[], double x);//秦九韶算法

#define MAXK 1e7

int main()
{
	int i;
	double a[MAXN];
	for (i = 0; i < MAXN; i++)
		a[i] = (double)i;

	//for (i = 0; i < MAXN; i++)
	//	printf("%.2f\n", a[i]);

	start = clock();
	for (i = 0; i < MAXK; i++) {
		fun(MAXN - 1, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK / MAXK;//平均一次的时间
	printf("tick1 = %f\n", (double)(stop - start));
	printf("duration1 = %6.2e\n", duration);

	start = clock();
	for (i = 0; i < MAXK; i++) {
		qin(MAXN - 1, a, 1.1);
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK / MAXK;
	printf("tick2 = %f\n", (double)(stop - start));
	printf("duration2 = %6.2e\n", duration);


	return 0;
}

double fun(int n, double a[], double x)
{
	int i;
	double p = a[0];
	for (i = 1; i <= n; i++){
		p += a[i] * pow(x, n);
	}
	return p;
}

double qin(int n, double a[], double x)
{
	int i;
	double p = a[n];
	for (i = n; i > 0; i--) {
		p = a[i - 1] + x * p;
	}
	return p;
}

//被测函数太快了，那就让他多跑几次，然后取平均值
//秦快了一个数量级