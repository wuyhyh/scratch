//����һ��ֻ����СдӢ����ĸ�����ֵ��ַ��������ղ�ͬ�ַ�ͳ�Ƹ����ɶൽ�����ͳ�ƽ����
//���ͳ�Ƶĸ�����ͬ������ASCII����С�������������

#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>
#include<vector>
using namespace std;

//���cmp����Ҫ��ס
bool cmp(pair<int, char> a, pair<int, char> b) {
	if (a.first == b.first) {//�����ִ�����ͬʱ
		return a.second < b.second;//���ASCII���С���ַ�
	}
	return a.first > b.first;//������ִ����϶���ַ�
}

string statistics(string str)
{
	string alpha_tab = "abcdefghijklmnopqrstuvwxyz";
	string num_tab = "0123456789";
	int digit[10] = { 0 };
	int alpha[26] = { 0 };
	for (int i = 0; i < str.size(); i++) {
		if (isalpha(str[i])) {
			alpha[str[i] - 'a']++;
		}
		else {
			digit[str[i] - '0']++;
		}
	}

	vector<pair<int, char>> vecp;
	for (int i = 0; i < 26; i++) {
		if (alpha[i] != 0) {
			vecp.push_back(pair<int, char>(alpha[i], alpha_tab[i]));
		}
	}
	for (int i = 0; i < 10; i++) {
		if (digit[i] != 0) {
			vecp.push_back(pair<int, char>(digit[i], num_tab[i]));
		}
	}

	sort(vecp.begin(), vecp.end(), cmp);
	string res;
	vector<pair<int, char>>::iterator it;
	for (it = vecp.begin(); it != vecp.end(); it++) {
		res += it->second;
	}

	return res;
}


int main()
{
	string str;
	while (cin >> str) {
		cout << statistics(str) << endl;
	}

	return 0;
}
