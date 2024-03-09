//����һ���ַ��������ַ�������Сд��ĸ��ɣ�
//��������ַ����ġ�Ư���ȡ�����������ĸ��Ư���ȡ����ܺ͡�
//ÿ����ĸ����һ����Ư���ȡ�����Χ��1��26֮�䡣
//û���κ�������ͬ��ĸӵ����ͬ�ġ�Ư���ȡ�����ĸ���Դ�Сд��
//��������ַ���������ÿ���ַ��������ܵġ�Ư���ȡ���

#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

string alpha_t = "abcdefghijklmnopqrstuvwxyz";

bool cmp(pair<char, int> a, pair<char, int> b)
{
	return a.second - b.second > 0;
}

int compute_score(string name)
{
	int alpha_count[26] = { 0 };
	for (int i = 0; i < name.size(); i++) {
		alpha_count[name[i] - 'a']++;
	}
	string name_single;
	for (int i = 0; i < 26; i++) {
		if (alpha_count[i] != 0) {
			name_single += alpha_t[i];
		}
	}

	vector<pair<char, int>> vp;//��ÿ����ĸ�����ǵĳ��ִ���������
	for (int i = 0; i < name_single.size(); i++) {
		pair<char, int> temp = make_pair(name_single[i], alpha_count[name_single[i] - 'a']);
		vp.push_back(temp);
	}
	sort(vp.begin(), vp.end(), cmp);
	vector<int> count;
	for (int i = 0; i < vp.size(); i++) {
		count.push_back(vp[i].second);
		vp[i].second = 26 - i;
	}

	int score = 0;
	for (int i = 0; i < vp.size(); i++) {
		score += (vp[i].second * count[i]);
	}
	return score;
}

int main()
{
	int n;
	while (cin >> n) {
		string name;
		vector<int> score;
		for (int i = 0; i < n; i++) {
			cin >> name;
			score.push_back(compute_score(name));
		}

		for (int i : score) {
			cout << i << endl;
		}
	}

	return 0;
}
