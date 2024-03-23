//任意一个偶数（大于2）都可以由2个素数组成，组成偶数的2个素数有很多种情况，
//本题目要求输出组成指定偶数的两个素数差值最小的素数对。

#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//检测素数
bool is_prime(int x)
{
	for (int i = 2; i <= sqrt(x); i++) {//这里必须用等号
		if (x % i == 0)
			return false;
	}
	return true;
}

vector<int> min_Gedebahe(int even)
{
	vector<int> result;
	int start = even / 2;
	for (int i = start; i < even; i++) {
		if (is_prime(i) && is_prime(even - i)) {
			result.push_back(i);
			result.push_back(even - i);
		}
	}

	return result;
}

int main() 
{
	int even;
	while (cin >> even) {
		vector<int> gede = min_Gedebahe(even);
		cout << gede[1] <<'\n' << gede[0] << endl;
	}
}

