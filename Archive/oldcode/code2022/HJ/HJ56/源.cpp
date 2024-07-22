//��ȫ����Perfect number�����ֳ����������걸������һЩ�������Ȼ����
//
//�����е������ӣ����������������Լ�����ĺͣ������Ӻ�������ǡ�õ���������
//
//���磺28������Լ��1��2��4��7��14��28����ȥ������28�⣬����5������ӣ�1 + 2 + 4 + 7 + 14 = 28��


#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

//����һ�����Ƿ�������
bool is_prime(int x)
{
	for (int i = 2; i < sqrt(x); i++) {//��С��������2���������������ܴ�������ţ���ͼ����������е�����
		if (x % i == 0)
			return false;
	}
	return true;
}

//ŷ��ʹ��÷ɭ����������ȫ��
// ���p����������2^p-1Ҳ����������ô��2^p-1��X2^��p-1������һ����ȫ��

bool is_meisen(int x)
{
	int meisen = pow(2, x)-1;
	if (is_prime(meisen))
		return true;
	return false;
}

int main()
{
	int n; 
	while (cin >> n) {
		int count = 0;
		int perfect_num;
		for (int i = 2; i < sqrt(n); i++) {
			if (is_prime(i) && is_meisen(i)) {
				perfect_num = (pow(2, i)-1) * pow(2, i - 1);
				if(perfect_num>=2&&perfect_num<=n)
					count++;
			}
		}
		cout << count << endl;
	}

	return 0;
}