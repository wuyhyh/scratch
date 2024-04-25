//一个 DNA 序列由 A / C / G / T 四个字母的排列组合组成。
//G 和 C 的比例（定义为 GC - Ratio ）
//是序列中 G 和 C 两个字母的总的出现次数除以总的字母数目（也就是序列长度）。
//在基因工程中，这个比例非常重要。因为高的 GC - Ratio 可能是基因的起始点。
//给定一个很长的 DNA 序列，以及限定的子串长度 N ，
//请帮助研究人员在给出的 DNA 序列中从左往右找出 GC - Ratio 最高且长度为 N 的第一个子串。
//DNA序列为 ACGT 的子串有 : ACG, CG, CGT 等等，但是没有 AGT ， CT 等等

//滑动窗口的思想
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

int count_GC(string str)
{
	int GC = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == 'G' || str[i] == 'C') {
			GC++;
		}
	}
	return GC;
}

string max_GC_ratio(string str,int len)
{
	if (str.size() == len) {
		return str;
	}

	int max_GC = 0;
	vector<int> gc;
	for (int i = 0; i < str.size() - len; i++) {
		int temp = count_GC(str.substr(i, len));
		gc.push_back(temp);
		max_GC = (max_GC > temp) ? max_GC : temp;
	}

	for (int i = 0; i < gc.size(); i++) {
		if (gc[i] == max_GC) {
			return str.substr(i, len);
		}
	}
	return " ";
}

int main()
{
	string str;
	while (cin >> str) {
		int len;
		cin >> len;
		cout << max_GC_ratio(str, len) << endl;
	}

	return 0;
}
