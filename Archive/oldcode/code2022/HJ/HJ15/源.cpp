//����һ�� int �͵���������������� int ���������ڴ��д洢ʱ 1 �ĸ�����
//
//���ݷ�Χ����֤�� 32 λ�������ַ�Χ��

#include<bitset>
#include<iostream>
using namespace std;

int main() 
{
	int num;
	cin >> num;
	bitset<32> b(num);//��num��ʼ��һ��32λ���ȵ�λ���
	cout << b.count();//�����ĸ���

	return 0;
}