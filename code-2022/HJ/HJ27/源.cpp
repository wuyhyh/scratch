//����һ�����ʵġ��ֵܵ��ʡ�Ϊ�������õ�����ĸ˳��ע�����Խ�������Σ���
//������ӡ�ɾ�����޸�ԭ�е���ĸ�������ɵĵ��ʡ�
//�ֵܵ���Ҫ���ԭ���ĵ��ʲ�ͬ��
//���磺 ab �� ba ���ֵܵ��ʡ� ab �� ab �����ֵܵ��ʡ�
//���ڸ����� n �����ʣ������ٸ���һ������ x ������Ѱ�� x ���ֵܵ����
//���ֵ������к�ĵ� k ��������ʲô��
//ע�⣺�ֵ��п������ظ����ʡ�

#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

bool is_ascii_same(string self, string str)//���������ַ����������
{
	int self_num = 0;
	for (int i = 0; i < self.size(); i++) {
		self_num += (self[i] - 'a');
	}
	int str_num = 0;
	for (int i = 0; i < str.size(); i++) {
		str_num += (str[i] - 'a');
	}

	if (self_num == str_num) {
		return true;
	}
	else {
		return false;
	}
}

bool is_brother(string self, string str)
{
	if (self.compare(str) == 0) {//��ȫ��ͬ���ַ�������
		return false;
	}
	else {
		sort(self.begin(), self.end());
		sort(str.begin(), str.end());
		if (self.compare(str) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}

int main()
{
	int n;
	while (cin >> n) {
		vector<string> all_str;
		string temp_str;
		for (int i = 0; i < n; i++) {
			cin >> temp_str;
			all_str.push_back(temp_str);
		}
		string self;
		cin >> self;
		unsigned k;
		cin >> k;

		//ɸѡ
		vector<string> brothers;
		for (int i = 0; i < n; i++) {
			if (all_str[i].size() == self.size() && is_ascii_same(self, all_str[i])) {
				if (is_brother(self, all_str[i])) {
					brothers.push_back(all_str[i]);
				}
			}
		}

		if (brothers.empty()) {//û���ֵ�
			cout << 0 << endl;
		}
		else {
			sort(brothers.begin(), brothers.end());
			if (k > brothers.size()) {
				cout << brothers.size() << endl;
			}
			else {
				cout << brothers.size() << endl;
				cout << brothers[k - 1] << endl;
			}
		}
	}

	return 0;
}
