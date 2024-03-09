//接受一个只包含小写字母的字符串，然后输出该字符串反转后的字符串。（字符串长度不超过1000）

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main() 
{
	string str;
	while (cin >> str) {
		reverse(str.begin(), str.end());
		cout << str;
	}

	return 0;
}