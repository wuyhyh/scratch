//����һ�� int �����������մ���������Ķ�˳�򣬷���һ�������ظ����ֵ��µ�������
//��֤������������һλ���� 0 ��


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
			if (set_ch.count(ch) != 1) {//set����������ֹ����ν���result
				result += ch;
				set_ch.insert(ch);
			}
		}
		cout << stoi(result) << endl;
	}

	return 0;
}
