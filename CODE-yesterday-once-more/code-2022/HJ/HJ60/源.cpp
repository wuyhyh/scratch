//����һ��ż��������2����������2��������ɣ����ż����2�������кܶ��������
//����ĿҪ��������ָ��ż��������������ֵ��С�������ԡ�

#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//�������
bool is_prime(int x)
{
	for (int i = 2; i <= sqrt(x); i++) {//��������õȺ�
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

