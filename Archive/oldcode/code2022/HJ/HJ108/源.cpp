//正整数A和正整数B 的最小公倍数是指 能被A和B整除的最小的正整数值，
//设计一个算法，求输入A和B的最小公倍数。

//数学原理：短除法：所有公共除数与所有余数之积，即为最小公倍数。

//数学原理2：最小公倍数 = 两数乘积除以他们的最大公约数

//数学原理3：可以使用更相减损术求出最大公约数、\
更相减损法是拿两个数中的较大值减去较小值，然后在减数、被减数、\
差之间选取两个较小值继续相减，直到减数和被减数相等，得出的数就是最大公约数。

#include<iostream>
using namespace std;

//求最大公约数
int genxiangjiansun(int beijianshu, int jianshu)
{
	if (beijianshu == jianshu)//递归结束条件
		return jianshu;

	if (beijianshu > jianshu) {
		int cha = beijianshu - jianshu;
		return genxiangjiansun(cha, jianshu);
	}
	else{
		int cha = jianshu - beijianshu;
		return genxiangjiansun(cha, beijianshu);
	}
}

//欧几里得算法求最大公约数
int gcd(int p, int q)
{
	if (q == 0)//递归退出条件
		return  p;

	int r = p % q;
	return gcd(q, r);
}

int main()
{
	int a, b;
	cin >> a >> b;
	int max = genxiangjiansun(a, b);
	cout << a * b / gcd(a,b);

	return 0;
}