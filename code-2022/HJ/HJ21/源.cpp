//现在有一种密码变换算法。
//九键手机键盘上的数字与字母的对应： 1--1， abc--2, def--3, 
//ghi--4, jkl--5, mno--6, pqrs--7, tuv--8 wxyz--9, 0--0，
//把密码中出现的小写字母都变成九键键盘对应的数字，如：a 变成 2，x 变成 9.
//而密码中出现的大写字母则变成小写之后往后移一位，如：X ，
//先变成小写，再往后移一位，变成了 y ，例外：Z 往后移是 a 。
//数字和其它的符号都不做变换。


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