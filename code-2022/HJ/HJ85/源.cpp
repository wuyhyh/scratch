//����һ��������Сд��ĸ���ַ�����������������Ӵ��ĳ��ȡ�
//��ν���Ĵ���ָ���ҶԳƵ��ַ�����
//��ν�Ӵ���ָһ���ַ���ɾ���䲿��ǰ׺�ͺ�׺��Ҳ���Բ�ɾ�����ַ���

#include<stack>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

//�����ظ�����ĸ�޷�����
int find_symetry(string str)
{
	stack<char> s_stack;
	stack<char> buff1;
	stack<char> buff2;
	string symetry;
	int max = 0;
	s_stack.push(str[0]);
	for (int i = 1; i < str.size(); i++) {
		if (str[i] == s_stack.top()) {
			symetry = s_stack.top() + symetry + str[i];
			buff1.push(s_stack.top());
			s_stack.pop();
			max = (max > symetry.size()) ? max : symetry.size();
		}
		else {
			symetry.clear();
			while (!buff1.empty()) {
				s_stack.push(buff1.top());
				buff2.push(buff1.top());
				buff1.pop();
			}
			while (!buff2.empty()) {
				s_stack.push(buff2.top());
				buff2.pop();
			}
			s_stack.push(str[i]);
		}
	}

	return max;
}

int main()
{
	string s;
	while (cin >> s) {
		cout << find_symetry(s) << endl;
	}

	return 0;
}
