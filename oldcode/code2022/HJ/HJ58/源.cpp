//����n���������ҳ�������С��k�����������������
//
//�����ж�����������

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int n;
	int k;
	vector<int> vec;
	int num;
	while (cin >> n >> k) {
		for (int i = 0; i < n; i++) {
			cin >> num;
			vec.push_back(num);
		}
		sort(vec.begin(), vec.end());
		for (int i = 0; i < k; i++) {
			cout << vec[i] << ' ';
		}
	}
	
	return 0;
}