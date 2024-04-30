//首先输入要输入的整数个数n，然后输入n个整数。输出为n个整数中负数的个数，
//和所有正整数的平均值，结果保留一位小数。
//0即不是正整数，也不是负数，不计入计算。如果没有正数，则平均值为0。

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double average(vector<int>& vec, int& minus)
{
	int count = 0;
	int sum = 0;
	minus = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > 0) {
			sum += vec[i];
			count++;
		}
		else if(vec[i]<0) {
			minus++;
		}
		else {
			;
		}
	}

	if (count == 0) {
		return 0.0;
	}
	else {
		double ave = (sum * 1.0) / count;
		return ave;
	}
}

int main() 
{
	int n;
	while (cin >> n) {
		int num;
		vector<int> vec_int;
		for (int i = 0; i < n; i++) {
			cin >> num;
			vec_int.push_back(num);
		}

		int minus;
		double res = average(vec_int,minus);
		cout << minus << ' ';
		printf("%.1f\n", res);
	}

	return 0;
}
