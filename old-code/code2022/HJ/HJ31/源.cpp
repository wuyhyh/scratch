//���ַ����е����е��ʽ��е��š�
//
//˵����
//
//1�����ɵ��ʵ��ַ�ֻ��26����д��СдӢ����ĸ��
//
//2���ǹ��ɵ��ʵ��ַ�����Ϊ���ʼ������
//
//3��Ҫ���ź�ĵ��ʼ������һ���ո��ʾ�����ԭ�ַ��������ڵ��ʼ��ж�������ʱ��
//����ת����Ҳֻ�������һ���ո�������
//
//4��ÿ�������20����ĸ��

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cctype>
#include<sstream>
#include<stack>
using namespace std;

void create_new(string str)
{
	int len = str.size();
	for (int i = 0; i < len; i++) {
		if (!isalpha(str[i])){
			str[i] = ' ';
		}
	}
	stringstream ss(str);//ʹ���ַ��������ַ����ǳ�����
	string word;
	stack<string> s_stack;
	while (ss>>word) {
		s_stack.push(word);
	}

	while (!s_stack.empty()) {
		cout << s_stack.top() << ' ';
		s_stack.pop();
	}

}

int main() 
{
	string str;
	while (getline(cin,str)) {
		create_new(str);
	}

	return 0;
}
