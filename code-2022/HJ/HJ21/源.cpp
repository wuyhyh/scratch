//������һ������任�㷨��
//�ż��ֻ������ϵ���������ĸ�Ķ�Ӧ�� 1--1�� abc--2, def--3, 
//ghi--4, jkl--5, mno--6, pqrs--7, tuv--8 wxyz--9, 0--0��
//�������г��ֵ�Сд��ĸ����ɾż����̶�Ӧ�����֣��磺a ��� 2��x ��� 9.
//�������г��ֵĴ�д��ĸ����Сд֮��������һλ���磺X ��
//�ȱ��Сд����������һλ������� y �����⣺Z �������� a ��
//���ֺ������ķ��Ŷ������任��


#include<iostream>
#include<string>
#include<cctype>
using namespace std;

string code_trans(string str)
{
	string str_trans;
	int len = str.size();
	for (int i = 0; i < len; i++) {
		if (isdigit(str[i])) {
			str_trans += str[i];
		}
		else if (isalpha(str[i])) {
			if (islower(str[i])) {
				switch (str[i]) {
				case 'a':
				case 'b':
				case 'c':str_trans += '2'; break;
				case 'd':
				case 'e':
				case 'f':str_trans += '3'; break;
				case 'g':
				case 'h':
				case 'i':str_trans += '4'; break;
				case 'j':
				case 'k':
				case 'l':str_trans += '5'; break;
				case 'm':
				case 'n':
				case 'o':str_trans += '6'; break;
				case 'p':
				case 'q':
				case 'r':
				case 's':str_trans += '7'; break;
				case 't':
				case 'u':
				case 'v':str_trans += '8'; break;
				default:
					str_trans += '9'; break;
				}
			}
			else if (isupper(str[i])) {
				if(str[i]=='Z'){
					str_trans += 'a';
				}
				else {
					str_trans += tolower(str[i] + 1);
				}
			}
		}
	}

	return str_trans;
}

int main()
{
	string str;
	cin >> str;
	cout << code_trans(str) << endl;

	return 0;
}