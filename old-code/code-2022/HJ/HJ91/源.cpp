//�����n* m�����̸��ӣ�nΪ����ĸ�������mΪ����ĸ�������
//���������Ͻǳ������ű�Ե�ߴ����Ͻ��ߵ����½ǣ��ܹ��ж������߷���
//Ҫ�����߻�ͷ·������ֻ�����Һ������ߣ���������������ߡ�

#include <iostream>
#include <vector>
using namespace std;

//���������combinaion(m+n,m);
int factorial(int n)
{
	int res = 1;
	for (int i = 1; i <= n; i++) {
		res *= i;
	}
	return res;
}

int main() 
{
	int right;
	int downward;
	cin >> right >> downward;
	int m = downward;
	int n = right + downward;
	int fenzi = factorial(n);
	int fenmu = factorial(m) * factorial(n - m);
	int res = fenzi / fenmu;
	cout << res << endl;

	return 0;
}
