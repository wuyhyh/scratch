//д��һ�����򣬽���һ����������ֵ���������ֵ�Ľ�������ֵ��
//���С�������ֵ���ڵ��� 0.5, ����ȡ����С�� 0.5 ��������ȡ��

#include <iostream>
using namespace std;

int main() 
{
	double num;
	while (cin >> num) {
		int result = (num - (int)num) >= 0.5 ? int(num) + 1 : (int)num;
		cout << result;
	}

	return 0;
}
