#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int count;
	while (cin >> count) {//条件判断的时候就输入了count的值 cin>>只能处理一行的输入
		vector<int> list;
		for (int i = 0; i < count; i++) {
			int a;
			cin >> a;
			list.push_back(a);
		}
		int k;
		cin >> k;
		cout << list[count - k] << endl;
	}

	return 0;
}