//����n�����룬����������ȣ��ֱ�Ϊ m1, m2, m3��mn ��
//ÿ�������Ӧ������Ϊ x1, x2, x3...xn ��
//����Ҫ����Щ����ȥ�����������(����ͬһ��)�����ܳƳ������ֲ�ͬ��������
//ע�������������� 0

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<set>
using namespace std;

//set<int>��ʼ��Ϊ����0��ÿ��һ�����룬�ͺ�֮ǰ���е�setԪ����ӣ�������������룬
//���set��size�����������ܵ���Ŀ

vector<int> generate_fama(vector<int>& m, vector<int>& x)
{
	vector<int> fama;
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < x[i]; j++)
			fama.push_back(m[i]);
	}
	return fama;
}

int varity(vector<int>& fama)
{
	set<int> se;//��ʼ�����ϣ���������0
	se.insert(0);

	for (int i = 0; i < fama.size(); i++) {
		set<int> temp;
		for (int a : se) {
			a += fama[i];
			temp.insert(a);
		}

		for (int i : temp) {
			se.insert(i);
		}
		se.insert(fama[i]);
	}

	return se.size();
}

int main()
{
	int n;
	while (cin >> n) {
		vector<int> m, x;
		for (int i = 0; i < n; i++) {
			int mm;
			cin >> mm;
			m.push_back(mm);
		}
		for (int i = 0; i < n; i++) {
			int xx;
			cin >> xx;
			x.push_back(xx);
		}

		vector<int> fama = generate_fama(m, x);
		cout << varity(fama) << endl;
	}

	return 0;
}
