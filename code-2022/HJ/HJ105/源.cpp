//���� n ����������ͳ�����еĸ��������������зǸ�����ƽ��ֵ��
//�������һλС�������û�зǸ�������ƽ��ֵΪ0
//�����ж����������ݣ����뵽�ļ�ĩβ��

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdio>
using namespace std;

double average(vector<int> vec,int& minus)
{
	int sum = 0;
	int count = 0;
	minus = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] >= 0) {
			sum += vec[i];
			count++;
		}
		else {
			minus++;
		}
	}
	if (count == 0) {
		return 0.0;
	}
	else {
		return (sum * 1.0) / count;
	}
}

int main()
{
	vector<int> vec_int;
	int n;
	while (cin >> n) {
		vec_int.push_back(n);
	}
	int minus = 0;
	double ave = average(vec_int, minus);
	cout << minus << endl;
	printf("%.1f", ave);

	return 0;
}
