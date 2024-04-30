//图片整理
//Lily上课时使用字母数字图片教小朋友们学习英语单词，每次都需要把这些图片按照大小
//（ASCII码值从小到大）排列收好。请大家给Lily帮忙，通过代码解决。
//Lily使用的图片使用字符"A"到"Z"、"a"到"z"、"0"到"9"表示。


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using  namespace std;

int main()
{
	string line;
	getline(cin, line);
	vector<char> ch_vec;
	for (int i = 0; i < line.size(); i++) {
		ch_vec.push_back(line[i]);
	}
	sort(ch_vec.begin(), ch_vec.end());
	for (int i = 0; i < ch_vec.size(); i++) {
		cout<<ch_vec[i];
	}

	return 0;
}