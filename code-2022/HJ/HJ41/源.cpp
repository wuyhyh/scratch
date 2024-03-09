//现有n种砝码，重量互不相等，分别为 m1, m2, m3…mn ；
//每种砝码对应的数量为 x1, x2, x3...xn 。
//现在要用这些砝码去称物体的重量(放在同一侧)，问能称出多少种不同的重量。
//注：称重重量包括 0

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<set>
using namespace std;

//set<int>初始化为重量0，每来一个砝码，就和之前所有的set元素相加，并插入这个砝码，
//最后set的size就是重量可能的数目

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
	set<int> se;//初始化集合，放入重量0
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
