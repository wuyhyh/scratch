//将一个英文语句以单词为单位逆序排放。例如“I am a boy”，逆序排放后为“boy a am I”
//
//所有单词之间用一个空格隔开，语句中除了英文字母外，不再包含其他字符

#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;

int main() {
	string str;
	stack<string> s_str;
	while (cin >> str) {
		s_str.push(str);
	}
	while (!s_str.empty()) {
		cout << s_str.top() << ' ';
		s_str.pop();
	}
	return 0;
}
