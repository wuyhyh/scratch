//��������ַ������мӽ��ܣ��������
//���ܷ���Ϊ��
//��������Ӣ����ĸʱ���ø�Ӣ����ĸ�ĺ�һ����ĸ�滻��ͬʱ��ĸ�任��Сд, 
//����ĸaʱ���滻ΪB����ĸZʱ���滻Ϊa��
//������������ʱ��Ѹ����ּ�1����0�滻1��1�滻2��9�滻0��
//�����ַ������仯��
//���ܷ���Ϊ���ܵ�����̡�

#include <string>
#include <iostream>
#include<cctype>
using namespace std;

string digit_tab = "1234567890";
string alpha_tab = "bcdefghijklmnopqrstuvwxyza";
string Alpha_tab = "BCDEFGHIJKLMNOPQRSTUVWXYZA";

string encode(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i])) {
			str[i] = digit_tab[str[i] - '0'];
		}
		else if (isupper(str[i])) {
			str[i] = alpha_tab[str[i] - 'A'];
		}
		else if(islower(str[i])) {
			str[i] = Alpha_tab[str[i] - 'a'];
		}
		else {
			;
		}
	}

	return str;
}

string digit_t = "9012345678";
string alpha_t = "zabcdefghijklmnopqrstuvwxy";
string Alpha_t = "ZABCDEFGHIJKLMNOPQRSTUVWXY";

string decode(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i])) {
			str[i] = digit_t[str[i] - '0'];
		}
		else if (isupper(str[i])) {
			str[i] = alpha_t[str[i] - 'A'];
		}
		else if (islower(str[i])) {
			str[i] = Alpha_t[str[i] - 'a'];
		}
		else {
			;
		}
	}

	return str;
}

int main() 
{
	string str1, str2;
	cin >> str1 >> str2;
	cout << encode(str1) << endl;
	cout << decode(str2) << endl;

	return 0;
}
