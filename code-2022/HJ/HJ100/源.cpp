//等差数列 2，5，8，11，14。。。。
//（从 2 开始的 3 为公差的等差数列）
//输出求等差数列前n项和

#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

double sum(int n)
{
	int a1 = 2;
	int d = 3;
	int an = a1 + (n - 1) * d;
	double Sn = ((a1 + an)*1.0) / 2 * n;
	return Sn;
}

int main()
{
	int n;
	while (cin >> n) {
		printf("%.0f \n", sum(n));
	}

	return 0;
}

