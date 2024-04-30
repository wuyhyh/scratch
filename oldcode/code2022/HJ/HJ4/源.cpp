//把连续输入的字符串分隔成长度为8的字符串输出，不足8的在后面补0

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

int main() 
{
	string str;
	while(cin>>str);
	{
		if (!str.empty()) {
			if (str.size() % 8 != 0) {
				string temp = "00000000";
				str = str + temp.substr(1, 8 - str.size() % 8);
			}

			for (int i = 0; i <= str.size()-8; i += 8) {
				for (int j = i; j < i + 8; j++)
					printf("%c", str[j]);
				putchar('\n');
			}
		}
	}

	return 0;
}
