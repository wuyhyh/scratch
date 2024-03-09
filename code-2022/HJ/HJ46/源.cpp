//输入一个字符串和一个整数 k ，截取字符串的前k个字符并输出

#include <iostream>
#include <string>
using namespace std;

int main() 
{
	string str;
	int k;
	cin >> str >> k;
	cout << str.substr(0, k) << endl;// s.substr(pos, len)指定位置开始的长度

	return 0;
}

