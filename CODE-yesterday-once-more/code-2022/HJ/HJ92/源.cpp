//输入一个字符串，返回其最长的数字子串，以及其长度。
//若有多个最长的数字子串，则将它们全部输出（按原字符串的相对位置）


#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cctype>
#include<utility>
#include<algorithm>
using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b)
{
	return a.second > b.second;
}

vector<string> all_num_str(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			str[i] = ' ';
		}
	}

	stringstream ss;
	ss << str;
	vector<pair<string, int>> vp;
	string temp;
	while (ss >> temp) {
		pair<string, int> p = make_pair(temp, temp.size());
		vp.push_back(p);
	}
	sort(vp.begin(), vp.end(), cmp);
	int max = vp[0].second;
	vector<string> res;
	for (int i = 0; i < vp.size(); i++) {
		if (vp[i].second == max) {
			res.push_back(vp[i].first);
		}
	}

	return res;
}

int main()
{
	string str;
	while (cin >> str) {
		vector<string> vec = all_num_str(str);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
		}
		cout <<',' << vec[0].size() << endl;
	}

	return 0;
}