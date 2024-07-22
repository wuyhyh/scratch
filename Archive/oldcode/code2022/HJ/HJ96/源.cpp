//��һ���ַ��������е�����ǰ����Ϸ��š�* ����
//�����ַ����ֲ��䡣������������Ϊһ������

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include<cctype>
using namespace std;

string str_add(string str)
{
	string res;
	int len = str.size();
	int other_count = 0;
	int digit_count = 0;
	string temp1 = str;
	string temp2 = str;
	for (int i = 0; i < len; i++) {//ֻʣ����Ƭ��
		if (!isdigit(temp1[i])) {
			temp1[i] = ' ';
			other_count++;
		}
	}
	for (int i = 0; i < len; i++) {//ֻʣ������Ƭ��
		if (isdigit(temp2[i])) {
			temp2[i] = ' ';
			digit_count++;
		}
	}

	if (digit_count == len) {
		return '*' + str + '*';
	}
	if (other_count == len) {
		return str;
	}

	stringstream ss1;
	stringstream ss2;
	ss1 << temp1;
	ss2 << temp2;

	string s1;
	vector<string> subA;//����
	while (ss1 >> s1) {
		subA.push_back('*' + s1 + '*');
	}
	string s2;
	vector<string> subB;//������
	while (ss2 >> s2) {
		subB.push_back(s2);
	}

	if (subA.size() > subB.size()) {
		subB.push_back(" ");
	}
	if (subA.size() < subB.size()) {
		subA.push_back(" ");
	}

	if (isdigit(str[0])) {//���ֿ�ͷ
		for (int i = 0; i < subA.size(); i++) {
			res += subA[i];//����
			res += subB[i];//������
		}
	}
	else {
		for (int i = 0; i < subA.size(); i++) {
			res += subB[i];//������
			res += subA[i];//����
		}
	}

	return res;
}

int main()
{
	string str;
	while (cin >> str) {
		cout << str_add(str) << endl;
	}

	return 0;
}
