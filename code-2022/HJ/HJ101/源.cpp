//������������������ʶ������Ԫ�ذ�����������������

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		int num;
		vector<int> vec;
		for (int i = 0; i < n; i++) {
			cin >> num;
			vec.push_back(num);
		}
		sort(vec.begin(), vec.end());
		int model;
		cin >> model;
		if (model == 1) {
			reverse(vec.begin(), vec.end());
		}
		for (int i = 0; i < n; i++) {
			cout << vec[i] << ' ';
		}
		cout << endl;
	}

	return 0;
}

