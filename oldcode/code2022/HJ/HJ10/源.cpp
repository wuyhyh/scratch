//��дһ�������������ַ����к��еĲ�ͬ�ַ��ĸ������ַ��� ASCII �뷶Χ��
//(0~127 ������ 0 �� 127)�����б�ʾ���������������ַ�����ڷ�Χ�ڵĲ���ͳ�ơ������ͬ���ַ�ֻ����һ��
//���磬�����ַ��� abaca ���ԣ��� a��b��c ���ֲ�ͬ���ַ��������� 3 ��

#include<iostream>
#include<string>
#include<set>
using namespace std;

int main() 
{
	string str;
	while (cin >> str) {
		set<char> set_ch;
		char ch;
		for (char ch: str) {
			if (set_ch.find(ch)==set_ch.end()) {
				set_ch.insert(ch);
			}
		}

		cout << set_ch.size();
	}

	return 0;
}