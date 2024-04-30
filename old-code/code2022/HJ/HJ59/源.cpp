//找出字符串中第一个只出现一次的字符

#include<iostream>
#include<string>
#include<vector>
using namespace std;

//使用数组散列
void first_only_one(string str)
{
	int count_table[128] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		count_table[str[i]]++;
	}

	bool is_find = false;
	for (int i = 0; i < str.size(); i++) {
		if (count_table[str[i]] == 1) {
			is_find = true;
			cout << str[i] << endl;
			break;
		}
	}

	if (is_find==false) {
		cout << -1 << endl;
	}
}

int main() 
{
	string str;
	while (cin >> str) {
		first_only_one(str);
	}

	return 0;
}