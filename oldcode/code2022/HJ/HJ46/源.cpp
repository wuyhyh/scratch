//����һ���ַ�����һ������ k ����ȡ�ַ�����ǰk���ַ������

#include <iostream>
#include <string>
using namespace std;

int main() 
{
	string str;
	int k;
	cin >> str >> k;
	cout << str.substr(0, k) << endl;// s.substr(pos, len)ָ��λ�ÿ�ʼ�ĳ���

	return 0;
}

