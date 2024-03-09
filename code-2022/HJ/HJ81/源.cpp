//�ж϶��ַ���S�е������ַ��Ƿ��ڳ��ַ���T��ȫ�����֡�
//��ע�Ȿ���ж����������롣

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;

//�������ַ����ϲ���ͳ���ظ��ַ����ֵĴ�����
//����ظ��Ĵ������ڶ��ַ����ĳ��ȣ����true

string unique_str(string str)
{
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	int count[26] = { 0 };//ͳ������
	for (int i = 0; i < str.size(); i++) {
		count[str[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {//���ظ�����������Ϊ1
		if (count[i] > 1)
			count[i] = 1;
	}
	string res;
	for (int i = 0; i < 26; i++) {//�ؽ��ַ���
		if (count[i] == 1)
			res += alpha[i];
	}
	return res;
}

bool is_include(string duan, string chang)
{
	string merge = duan + chang;
	int count[26] = { 0 };
	for (int i = 0; i < merge.size(); i++) {
		count[merge[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {
		if (count[i] == 1)
			count[i] = 0;
	}

	int standard = 0;
	for (int i = 0; i < 26; i++) {
		if (count[i] != 0)
			standard++;
	}

	if (standard == duan.size())
		return true;
	else
		return false;
}

int main() 
{
	string duan;
	string chang;
	while (cin >> duan) {
		cin >> chang;
		string str_duan = unique_str(duan);
		string str_chang = unique_str(chang);
		if (is_include(str_duan, str_chang))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	
	return 0;
}
