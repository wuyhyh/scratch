//请计算n* m的棋盘格子（n为横向的格子数，m为竖向的格子数）
//从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，
//要求不能走回头路，即：只能往右和往下走，不能往左和往上走。

#include <iostream>
#include <vector>
using namespace std;

//计算组合数combinaion(m+n,m);
int factorial(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}

int main() 
{
	int right;
	int downward;
	cin >> right >> downward;
	int m = downward;
	int n = right + downward;
	int fenzi = factorial(n);
	int fenmu = factorial(m) * factorial(n - m);
	int res = fenzi / fenmu;
	cout << res << endl;

	return 0;
}
