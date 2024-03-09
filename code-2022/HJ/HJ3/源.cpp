//明明的随机数
//输入范围1~500的若干个随机数，把重复的去掉，并排序输出

//散列到一个500大的数组中就行了

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>

using namespace std;

int main()
{
	int count;
	vector<int> source_int;

	cin >> count;
	int num;
	while (cin >> num)
		source_int.push_back(num);

	int arr[502] = { 0 };
	for(int i=0;i<source_int.size();i++){
		if (source_int[i] == 500)
			arr[500] = source_int[i];
		else
			arr[source_int[i] % 500] = source_int[i];
	}

	for (int i = 1; i <= 500; i++) {
		if (arr[i] != 0)
			cout << arr[i] << endl;
	}

	return 0;
}