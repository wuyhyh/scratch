//�������ʽ��ĳһ����ֵ

#include<stdio.h>
#include<time.h>
#include<math.h>//pow()

clock_t start;
clock_t stop;
double duration;

#define MAXN 10//��ദ��9�׶���ʽ����10��

double fun(int n, double a[], double x);//�����㷨
double qin(int n, double a[], double x);//�ؾ����㷨

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
	duration = ((double)(stop - start)) / CLK_TCK / MAXK;//ƽ��һ�ε�ʱ��
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

//���⺯��̫���ˣ��Ǿ��������ܼ��Σ�Ȼ��ȡƽ��ֵ
//�ؿ���һ��������