//����һ��������������������ַ�������ʽ�������
//���򲻿��Ǹ���������������ֺ���0����������ʽҲ����0��������Ϊ100�������Ϊ001

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() 
{
	string str;
	while (cin >> str) {
		reverse(str.begin(), str.end());
		cout << str;
	}

	return 0;
}