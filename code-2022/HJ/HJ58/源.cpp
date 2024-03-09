//输入n个整数，找出其中最小的k个整数并按升序输出
//
//本题有多组输入样例

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