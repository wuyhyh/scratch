//对输入的字符串进行加解密，并输出。
//加密方法为：
//当内容是英文字母时则用该英文字母的后一个字母替换，同时字母变换大小写, 
//如字母a时则替换为B；字母Z时则替换为a；
//当内容是数字时则把该数字加1，如0替换1，1替换2，9替换0；
//其他字符不做变化。
//解密方法为加密的逆过程。

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
