//����һ���������߶��������£�ÿ����غ�����ԭ�߶ȵ�һ��; 
//������, �����ڵ�5�����ʱ�������������� ? ��5�η�����ߣ�

#include<iostream>
#include<cstdio>
using namespace std;

//���ó�ʼ�߶�Ϊh,����ȫ��Ϊh��1m����Ӧ����ĳ˻�

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
