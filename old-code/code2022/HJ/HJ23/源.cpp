//实现删除字符串中出现次数最少的字符，若出现次数最少的字符有多个，则把出现次数最少的字符都删除。
//输出删除这些单词后的字符串，字符串中其它字符保持原来的顺序。

#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

string delete_str(string str)
{
	int len = str.size();
	int arr_count[26] = { 0 };
	for (int i = 0; i < len; i++) {//统计各个小写字母出现的次数
		arr_count[str[i] - 'a'] += 1;
	}
	int min = len;
	for (int i = 0; i < 26; i++) {//找出字符串中最小次数的标准
		if (arr_count[i] <= min&&arr_count[i]!=0) {
			min = arr_count[i];
		}
	}
	//重建字符串
	string str_del;
	for (int i = 0; i < len; i++) {
		if (arr_count[str[i]-'a'] > min) {
			str_del += str[i];
		}
	}

	return str_del;
}

int main()
{
	string str;
	cin >> str;
	cout << delete_str(str) << endl;

	return 0;
}