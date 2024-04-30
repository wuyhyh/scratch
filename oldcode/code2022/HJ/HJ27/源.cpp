//定义一个单词的“兄弟单词”为：交换该单词字母顺序（注：可以交换任意次），
//而不添加、删除、修改原有的字母就能生成的单词。
//兄弟单词要求和原来的单词不同。
//例如： ab 和 ba 是兄弟单词。 ab 和 ab 则不是兄弟单词。
//现在给定你 n 个单词，另外再给你一个单词 x ，让你寻找 x 的兄弟单词里，
//按字典序排列后的第 k 个单词是什么？
//注意：字典中可能有重复单词。

#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

bool is_ascii_same(string self, string str)//两个参数字符串长度相等
{
	int self_num = 0;
	for (int i = 0; i < self.size(); i++) {
		self_num += (self[i] - 'a');
	}
	int str_num = 0;
	for (int i = 0; i < str.size(); i++) {
		str_num += (str[i] - 'a');
	}

	if (self_num == str_num) {
		return true;
	}
	else {
		return false;
	}
}

bool is_brother(string self, string str)
{
	if (self.compare(str) == 0) {//完全相同的字符串舍弃
		return false;
	}
	else {
		sort(self.begin(), self.end());
		sort(str.begin(), str.end());
		if (self.compare(str) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

int main()
{
	int n;
	while (cin >> n) {
		vector<string> all_str;
		string temp_str;
		for (int i = 0; i < n; i++) {
			cin >> temp_str;
			all_str.push_back(temp_str);
		}
		string self;
		cin >> self;
		unsigned k;
		cin >> k;

		//筛选
		vector<string> brothers;
		for (int i = 0; i < n; i++) {
			if (all_str[i].size() == self.size() && is_ascii_same(self, all_str[i])) {
				if (is_brother(self, all_str[i])) {
					brothers.push_back(all_str[i]);
				}
			}
		}

		if (brothers.empty()) {//没有兄弟
			cout << 0 << endl;
		}
		else {
			sort(brothers.begin(), brothers.end());
			if (k > brothers.size()) {
				cout << brothers.size() << endl;
			}
			else {
				cout << brothers.size() << endl;
				cout << brothers[k - 1] << endl;
			}
		}
	}

	return 0;
}
