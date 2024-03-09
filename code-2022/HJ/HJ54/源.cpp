//����һ���ַ����������������ʽ����������ֵ��
//
//�����ַ������Ȳ����� 100 ���Ϸ����ַ����� �� + , -, *, / , (, )�� �� ��0 - 9�� ��

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;

stack<int> get_op_num(string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			str[i] = ' ';
		}
	}
	stack<int> op_num;
	stringstream ss(str);
	string s;
	while (ss >> s) {
		op_num.push(stoi(s));
	}
	return op_num;
}


int compute(string str)
{
	int result;
	stack<int> values = get_op_num(str);
	stack<char> op;
	str = str + ')';
	for (int i = 0; i < str.size(); i++) {
		if (!isdigit(str[i])) {
			char c = str[i];
			switch (c) {
			case '(':break;
			case '+':op.push(c); break;
			case '-':op.push(c); break;
			case '*':op.push(c); break;
			case '/':op.push(c); break;
			case ')': {					//��ʼ����
				char oper = op.top(); op.pop();
				if (oper == '+') {
					int v1 = values.top(); values.pop();
					int v2 = values.top(); values.pop();
					values.push(v1 + v2);
				}
				else if (oper == '-') {
					int v1 = values.top(); values.pop();
					int v2 = values.top(); values.pop();
					values.push(v2 - v1);
				}
				else if (oper == '*') {
					int v1 = values.top(); values.pop();
					int v2 = values.top(); values.pop();
					values.push(v2 * v1);
				}
				else if (oper == '/') {
					int v1 = values.top(); values.pop();
					int v2 = values.top(); values.pop();
					if (v1 != 0) 
						values.push(v1 / v1);
					else
						return -1;
				}break;
			}
			}
		}
	}
	result = values.top();
	return result;
}

int main()
{
	string str;
	while (cin >> str) {
		cout << compute(str) << endl;
	}

	return 0;
}
