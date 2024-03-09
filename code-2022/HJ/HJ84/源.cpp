//找出给定字符串中大写字符(即'A' - 'Z')的个数。

#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int count_upper(string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); i++) {
		if (isupper(str[i]))
			count++;
	}

	return count;
}

int main() 
{
	int cnt;
	string str;
	while (getline(cin, str)) {
		cout << count_upper(str) << endl;
	}

	return 0;
}
