//给出一个字符串，该字符串仅由小写字母组成，
//定义这个字符串的“漂亮度”是其所有字母“漂亮度”的总和。
//每个字母都有一个“漂亮度”，范围在1到26之间。
//没有任何两个不同字母拥有相同的“漂亮度”。字母忽略大小写。
//给出多个字符串，计算每个字符串最大可能的“漂亮度”。

#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

string alpha_t = "abcdefghijklmnopqrstuvwxyz";

bool cmp(pair<char, int> a, pair<char, int> b)
{
	return a.second - b.second > 0;
}

int compute_score(string name)
{
	int alpha_count[26] = { 0 };
	for (int i = 0; i < name.size(); i++) {
		alpha_count[name[i] - 'a']++;
	}
	string name_single;
	for (int i = 0; i < 26; i++) {
		if (alpha_count[i] != 0) {
			name_single += alpha_t[i];
		}
	}

	vector<pair<char, int>> vp;//把每个字母和他们的出现次数绑定起来
	for (int i = 0; i < name_single.size(); i++) {
		pair<char, int> temp = make_pair(name_single[i], alpha_count[name_single[i] - 'a']);
		vp.push_back(temp);
	}
	sort(vp.begin(), vp.end(), cmp);
	vector<int> count;
	for (int i = 0; i < vp.size(); i++) {
		count.push_back(vp[i].second);
		vp[i].second = 26 - i;
	}

	int score = 0;
	for (int i = 0; i < vp.size(); i++) {
		score += (vp[i].second * count[i]);
	}
	return score;
}

int main()
{
	int n;
	while (cin >> n) {
		string name;
		vector<int> score;
		for (int i = 0; i < n; i++) {
			cin >> name;
			score.push_back(compute_score(name));
		}

		for (int i : score) {
			cout << i << endl;
		}
	}

	return 0;
}
