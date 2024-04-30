//输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。
//
//数据范围：输入的字符串长度满足 1 \le n \le 1000 \1≤n≤1000

#include <iostream>
#include <string.h>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

vector<int> char_statistics(string line)
{
	vector<int> result;
	int alpha = 0;
	int blank = 0;
	int num = 0;
	int other = 0;
	for (int i = 0; i < line.size(); i++) {
		if (isalpha(line[i])) {
			alpha++;
		}
		else if (isblank(line[i])) {
			blank++;
		}
		else if (isdigit(line[i])) {
			num++;
		}
		else {
			other++;
		}
	}
	result.push_back(alpha);
	result.push_back(blank);
	result.push_back(num);
	result.push_back(other);

	return result;
}

int main()
{
	string line;
	while (getline(cin, line)) {
		vector<int> conclusion = char_statistics(line);
		for (int i = 0; i < conclusion.size(); i++) {
			cout << conclusion[i] << endl;
		}
	}

	return 0;
}