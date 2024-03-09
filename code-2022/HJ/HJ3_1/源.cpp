#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int count;
	cin >> count;
	int num;
	list<int> ls_int;
	vector<int> vec_int;
	while (cin >> num) {
		vec_int.push_back(num);
	}
	sort(vec_int.begin(), vec_int.end());
	for (int i = 0; i < count; i++) {
		ls_int.push_back(vec_int[i]);
	}
	ls_int.unique();
	list<int>::iterator it;
	for (it = ls_int.begin(); it != ls_int.end(); it++) {
		cout << *it<< endl;
	}

	return 0;
}