#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int count;
	while (cin >> count) {//�����жϵ�ʱ���������count��ֵ cin>>ֻ�ܴ���һ�е�����
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