//输入两个用字符串 str 表示的整数，求它们所表示的数之和。

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//实现一个加法器
string adder(string str1, string str2)
{
	string res;
	//先统一长度
	int dis = str1.size() - str2.size();
	if ( dis > 0) {
		for(int i=0;i<dis;i++)
			str2.insert(str2.begin(), '0');
	}
	else if (dis < 0) {
		for (int i = 0; i < -dis; i++)
			str1.insert(str1.begin(), '0');
	}

	string num_tab = "0123456789";
	int add_num1 = 0;
	int add_num2 = 0;
	int carry = 0;
	for (int i = str1.size() - 1; i >= 0; i--) {
		add_num1 = str1[i] - '0';
		add_num2 = str2[i] - '0';
		int temp = add_num1 + add_num2 + carry;
		char temp_res = num_tab[temp % 10];
		if (temp >= 10) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		res.insert(res.begin(),temp_res);
	}

	//是否增加位数
	if (carry == 1) {
		res.insert(res.begin(), '1');
	}

	return res;
}

int main()
{
	string str1, str2;
	while (cin >> str1 >> str2) {
		cout << adder(str1, str2) << endl;
	}

	return 0;
}
