//����һ�����������������ڶ������µ�1�ĸ�����

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main() 
{
	int num;
	while (cin >> num) {
		bitset<32> binary(num);//��num��ʾ��32λ ����binary��
		cout << binary.count() << endl;//count()�����������1�ĸ���
	}

	return 0;
}