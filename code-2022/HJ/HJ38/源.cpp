//假设一个球从任意高度自由落下，每次落地后反跳回原高度的一半; 
//再落下, 求它在第5次落地时，共经历多少米 ? 第5次反弹多高？

#include<iostream>
#include<cstdio>
using namespace std;

//设置初始高度为h,则结果全部为h和1m所对应结果的乘积

double all_the_trip(int height)
{
	return (46.0 / 16) * height;
}

double fiveth_bounce(int height)
{
	return (1.0 / 32) * height;
}

int maisn()
{
	int height;
	while (cin >> height) {
		cout << all_the_trip(height) << endl;
		cout << fiveth_bounce(height) << endl;
	}

	return 0;
}
