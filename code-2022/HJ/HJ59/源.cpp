//�ҳ��ַ����е�һ��ֻ����һ�ε��ַ�

#include<iostream>
#include<string>
#include<vector>
using namespace std;

//ʹ������ɢ��
void first_only_one(string str)
{
	int count_table[128] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		count_table[str[i]]++;
	}

	bool is_find = false;
	for (int i = 0; i < str.size(); i++) {
		if (count_table[str[i]] == 1) {
			is_find = true;
			cout << str[i] << endl;
			break;
		}
	}

	if (is_find==false) {
		cout << -1 << endl;
	}
}

int main() 
{
	string str;
	while (cin >> str) {
		first_only_one(str);
	}

	return 0;
}