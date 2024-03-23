//输入一个 int 型整数，按照从右向左的阅读顺序，返回一个不含重复数字的新的整数。
//保证输入的整数最后一位不是 0 。


#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
	int nums;
	while (cin >> nums) {
		string str = to_string(nums);
		reverse(str.begin(), str.end());
		set<char> set_ch;
		string result;
		for (char ch : str) {
			if (set_ch.count(ch) != 1) {//set的作用是阻止其二次进入result
				result += ch;
				set_ch.insert(ch);
			}
		}
		cout << stoi(result) << endl;
	}

	return 0;
}
