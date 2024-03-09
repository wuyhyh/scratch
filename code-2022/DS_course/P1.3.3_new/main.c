//试试函数指针减少代码的重复

#include<stdio.h>
#include<math.h>
#include<time.h>

//两种方法计算多项式的值
double fun(int n, double a[], double x);
double qin(int n, double a[], double x);

#define MAXN 10
#define MAXK 1e7

void experiment(double(*fun)(int, double a[], double));

int main()
{
	experiment(&fun);
	experiment(&qin);

	return 0;
}

double fun(int n, double a[], double x)
{
	int i;
	double p = a[0];
	for (i = 1; i <= n; i++) {
		p += p * pow(x, i);
	}
	return p;
}

//n次多项式有n+1项，系数a0,a1...aN
double qin(int n, double a[], double x)
{
	int i;
	double p = a[n];
	for (i = n; i > 0; i--) {
		p = a[i - 1] + p * x;//只有n次乘法和加法
	}
	return p;
}

void experiment (double(*fun)(int n, double a[], double x))
{
	double a[MAXN];
	for (int i = 0; i < 10; i++) {
		a[i] = (double)i;
	}
	clock_t start, end;
	start = clock();
	for(int i=0;i<MAXK;i++)
		fun(MAXN - 1, a, 1.1);
	end = clock();

	double duration = (double)(end - start) / CLK_TCK/ MAXK;
	double tick = (end - start);
	
	printf("tick = %f\n", tick);
	printf("duration = %6.2e\n", duration);
}