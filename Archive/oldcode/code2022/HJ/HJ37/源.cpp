//��һ�����ӣ��ӳ������3������ÿ���¶���һֻ���ӣ�С���ӳ����������º�ÿ��������һֻ���ӡ�
//���ӣ�����һֻ���ӵ�3���³�������ô����5���¿�ʼ��ÿ������һֻ���ӡ�
//һ�µ�ʱ����һֻ���ӣ��������Ӷ��������ʵ�n���µ���������Ϊ���٣�
//���ݷ�Χ���������� 1 \le n \le31 \1��n��31

#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

//ʹ�õݹ��˼�룬��һ���£��ڶ������ǳ�ʼ������������·ݵ����ӵ��� �����ӵ�+֮ǰһ���µ�����

int rabbits(int month)
{
	if (month == 1)
		return 1;
	if (month == 2)
		return 1;

	int last_month = rabbits(month - 1);
	int birth_this_month = rabbits(month - 2);
	return last_month + birth_this_month;
}


int main() 
{
	int month;
	while(cin >> month)
		cout << rabbits(month) << endl;

	return 0;
}
