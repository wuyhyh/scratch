#include <iostream>
#include <string>
#include<set>
#include<vector>
using namespace std;

vector<string> substr_over2(string str)//存放所有长度大于2的子字符串
{
	vector<string> sub_str;
	for (int pos = 0; pos < str.size(); pos++) {
		for (int len = str.size() - pos; len >= 3; len--) {
			sub_str.push_back(str.substr(pos, len));
		}
	}
	return sub_str;
}

bool is_repeat(vector<string>& vec)//判断是否有重复的字符串
{
	set<string> set_str;
	for (string s : vec) {
		set_str.insert(s);
	}

	if (set_str.size() != vec.size()) {
		return true;
	}
	else {
		return false;
	}
}

bool is_symbol_varity(string str)//判断是否有四种字符中的三种
{
	int kinds[4] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		if (isupper(str[i])) {
			kinds[0]++;
		}
		else if (islower(str[i])) {
			kinds[1]++;
		}
		else if (isdigit(str[i])) {
			kinds[2]++;
		}
		else {
			kinds[3]++;
		}
	}

	int res = 0;
	for (int i = 0; i < 4; i++) {
		if (kinds[i] != 0) {
			res++;
		}
	}

	if (res >= 3) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	string str;
	while (cin >> str) {
		vector<string> vec = substr_over2(str);
		if (!is_repeat(vec) && is_symbol_varity(str) && str.size() > 8)
			cout << "OK" << endl;
		else
			cout << "NG" << endl;
	}

	return 0;
}
