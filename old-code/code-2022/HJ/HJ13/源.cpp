//��һ��Ӣ������Ե���Ϊ��λ�����ŷš����硰I am a boy���������ŷź�Ϊ��boy a am I��
//
//���е���֮����һ���ո����������г���Ӣ����ĸ�⣬���ٰ��������ַ�

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
