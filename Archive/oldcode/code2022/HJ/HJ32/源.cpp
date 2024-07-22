//Catcher是MCA国的情报员，他工作时发现敌国会用一些对称的密码进行通信，
//比如像这些ABBA，ABA，A，123321，
//但是他们有时会在开始或结束时加入一些无关的字符以防止别国破解。
//比如进行下列变化 ABBA->12ABBA, ABA->ABAKK, 123321->51233214　。
//因为截获的串太长了，而且存在多种可能的情况（abaaab可看作是aba, 或baaab的加密形式）
//Cathcer的工作量实在是太大了，他只能向电脑高手求助，
//你能帮Catcher找出最长的有效密码串吗
//
//最长回文字符串的长度

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

bool is_symetry(string str)
{
	int len = str.size();
	if (len % 2 == 0) {//长度为偶数
		int cut = len / 2;
		string subA = str.substr(0, cut);
		string subB = str.substr(cut, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {//长度为奇数
		int cut = len / 2;
		string subA = str.substr(0, cut);
		string subB = str.substr(cut+1, cut);
		reverse(subB.begin(), subB.end());
		if (subA.compare(subB) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

//暴力算法超时
int main()
{
	string str;
	cin >> str;
	int longest = 0;
	for (int pos = 0; pos < str.size(); pos++) {
		for (int len = str.size(); len >= 2; len--) {
			string sub = str.substr(pos, len);
			if (is_symetry(sub)) {
				longest = (sub.size() > longest) ? sub.size() : longest;
			}
		}
	}
	cout << longest << endl;

	return 0;
}