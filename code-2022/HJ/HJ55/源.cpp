//��� 1��n֮�� ���� 7 �й����ֵĸ�����
//һ������7�й���ָ������� 7 �ı����������ǰ��� 7 ������
//���� 17 ��27 ��37 ... 70 ��71 ��72 ��73...��

#include<iostream>
#include<vector>
using namespace std;

int main() 
{
	int n;
	while (cin >> n) {
		int cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			if ((i % 7) == 0) //7�ı���
				cnt++;
			else if ((i % 10) == 7 || (i / 10) % 10 == 7 || (i / 100) % 10 == 7 || (i / 1000) % 10 == 7) 
				cnt++;//����һλ����7
		}
		cout << cnt << endl;
	}

	return 0;
}