//����������
//����һ��ʮ�����Ƶ���ֵ�ַ�����
//
//���������
//�������ֵ��ʮ�����ַ�������ͬ��Ĳ���������\n������

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int power(int x, int n)
{
	int result = 1;
	for (int i = 1; i <= n; i++) {
		result *= x;
	}
	return result;
}

int main()
{
	string str;
	while (cin >> str) {
		unsigned int result = 0;
		string str_num = str.substr(2, str.size() - 1);
		int len = str_num.size()-1;
		for (int i = len; i >= 0; i--) {
			switch (str_num[i]) {
			case 'A':result += 10 * power(16, len - i); break;
			case 'a':result += 10 * power(16, len - i); break;
			case 'B':result += 11 * power(16, len - i); break;
			case 'b':result += 11 * power(16, len - i); break;
			case 'C':result += 12 * power(16, len - i); break;
			case 'c':result += 12 * power(16, len - i); break;
			case 'D':result += 13 * power(16, len - i); break;
			case 'd':result += 13 * power(16, len - i); break;
			case 'E':result += 14 * power(16, len - i); break;
			case 'e':result += 14 * power(16, len - i); break;
			case 'f':result += 15 * power(16, len - i); break;
			case 'F':result += 15 * power(16, len - i); break;
			default:result += (str_num[i]-'0') * power(16, len - i);
			}
		}
		cout << result << endl;
	}

	return 0;
}
