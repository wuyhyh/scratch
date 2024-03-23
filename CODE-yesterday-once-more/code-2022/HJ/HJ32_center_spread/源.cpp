//最长回文字符串的长度

//中心扩散法判断是否对称，有两中扩散的情况：ABA ABBA

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int spread(string str,int left,int right)
{
	int res = 0;
	while (left >= 0 && right <= str.size() - 1 && str[left] == str[right]) {
		left--;
		right++;
	}
	res = right - left - 1;
	return res;
}

int longest(string str)
{
	int max_len = 0;
	for (int i = 0; i < str.size(); i++) {
		//ABA
		int len1 = spread(str, i, i);
		//ABBA
		int len2 = spread(str, i, i + 1);
		int curr_max_len = (len1 > len2) ? len1 : len2;
		max_len = (max_len > curr_max_len) ? max_len : curr_max_len;
	}

	return max_len;
}

int main()
{
	string str;
	cin >> str;
	cout << longest(str) << endl;
	return 0;
}