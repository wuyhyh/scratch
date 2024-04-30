//将一个字符串中所有的整数前后加上符号“* ”，
//其他字符保持不变。连续的数字视为一个整数

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
	for (int i = 0; i < len; i++) {//只剩数字片段
		if (!isdigit(temp1[i])) {
			temp1[i] = ' ';
			other_count++;
		}
	}
	for (int i = 0; i < len; i++) {//只剩非数字片段
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
	vector<string> subA;//数字
	while (ss1 >> s1) {
		subA.push_back('*' + s1 + '*');
	}
	string s2;
	vector<string> subB;//非数字
	while (ss2 >> s2) {
		subB.push_back(s2);
	}

	if (subA.size() > subB.size()) {
		subB.push_back(" ");
	}
	if (subA.size() < subB.size()) {
		subA.push_back(" ");
	}

	if (isdigit(str[0])) {//数字开头
		for (int i = 0; i < subA.size(); i++) {
			res += subA[i];//数字
			res += subB[i];//非数字
		}
	}
	else {
		for (int i = 0; i < subA.size(); i++) {
			res += subB[i];//非数字
			res += subA[i];//数字
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
