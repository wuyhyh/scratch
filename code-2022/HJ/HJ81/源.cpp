//判断短字符串S中的所有字符是否在长字符串T中全部出现。
//请注意本题有多组样例输入。

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;

//把两个字符串合并，统计重复字符出现的次数，
//如果重复的次数等于短字符串的长度，输出true

string unique_str(string str)
{
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	int count[26] = { 0 };//统计数量
	for (int i = 0; i < str.size(); i++) {
		count[str[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {//把重复的数量重置为1
		if (count[i] > 1)
			count[i] = 1;
	}
	string res;
	for (int i = 0; i < 26; i++) {//重建字符串
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
