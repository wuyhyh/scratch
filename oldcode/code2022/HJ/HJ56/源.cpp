//完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
//
//它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
//
//例如：28，它有约数1、2、4、7、14、28，除去它本身28外，其余5个数相加，1 + 2 + 4 + 7 + 14 = 28。


#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

//检验一个数是否是素数
bool is_prime(int x)
{
	for (int i = 2; i < sqrt(x); i++) {//最小的质数是2，他的因数不可能大于其根号，这就检验了他所有的因数
		if (x % i == 0)
			return false;
	}
	return true;
}

//欧拉使用梅森素数构造完全数
// 如果p是质数，且2^p-1也是质数，那么（2^p-1）X2^（p-1）便是一个完全数

bool is_meisen(int x)
{
	int meisen = pow(2, x)-1;
	if (is_prime(meisen))
		return true;
	return false;
}

int main()
{
	int n; 
	while (cin >> n) {
		int count = 0;
		int perfect_num;
		for (int i = 2; i < sqrt(n); i++) {
			if (is_prime(i) && is_meisen(i)) {
				perfect_num = (pow(2, i)-1) * pow(2, i - 1);
				if(perfect_num>=2&&perfect_num<=n)
					count++;
			}
		}
		cout << count << endl;
	}

	return 0;
}