//����
//���� : ����һ�������������մ�С�����˳������������������ӣ��ظ���ҲҪ�о٣�����180��������Ϊ2 2 3 3 5 ��

#include<iostream>
#include <math.h>
using namespace std;

int main() 
{
	int num;
	while (cin >> num) {
		for (int prim = 2; prim <= sqrt(num); prim++) {
			while (num % prim == 0) {
				cout << prim << ' ';
				num = num / prim;
			}
		}
		if (num > 1)//ʣ�µĲ��ִ���1����������߱������������������
			cout << num << ' ';
	}

	return 0;
}