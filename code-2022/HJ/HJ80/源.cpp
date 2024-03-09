//将两个整型数组按照升序合并，并且过滤掉重复数组元素。
//输出时相邻两数之间没有空格

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
using namespace std;

string merge_int(vector<int> arr1, vector<int> arr2)
{
	list<int> ls;
	vector<int> merge;
	for (int i = 0; i < arr1.size(); i++) {
		merge.push_back(arr1[i]);
	}
	for (int i = 0; i < arr2.size(); i++) {
		merge.push_back(arr2[i]);
	}
	sort(merge.begin(), merge.end());
	for (int i = 0; i < merge.size(); i++) {
		ls.push_back(merge[i]);
	}

	ls.unique();
	string result;
	list<int>::iterator it;
	for (it=ls.begin(); it !=ls.end(); it++) {
		result += to_string(*it);
	}
	return result;
}

int main() 
{
	vector<int> a;
	vector<int> b;
	int n1;
	int n2;
	cin >> n1;
	for (int i = 0; i < n1; i++) {
		int temp;
		cin >> temp;
		a.push_back(temp);
	}
	cin >> n2;
	for (int i = 0; i < n2; i++) {
		int temp;
		cin >> temp;
		b.push_back(temp);
	}

	cout << merge_int(a, b) << endl;

	return 0;
}

