//给定 n 个字符串，请对 n 个字符串按照字典序排列。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int count;
	cin >> count;
	vector<string> vec_str(count);//数组
	for (int i = 0; i < count; i++){
		cin >> vec_str[i];
	}

	sort(vec_str.begin(), vec_str.end());
	for (string str : vec_str) {
		cout << str << endl;
	}

	return 0;
}