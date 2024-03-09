//蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。
//
//例如，当输入5时，应该输出的三角形为：
//
//1 3 6 10 15
//2 5 9 14
//4 8 13
//7 12
//11


#include <iostream>
#include <vector>
using namespace std;

vector<int> renew_row(vector<int> vec_row)
{
	for (int i = 1; i < vec_row.size(); i++) {
		vec_row[i] = vec_row[i] - 1;
	}
	vec_row.erase(vec_row.begin());
	return vec_row;
}

void print_row(vector<int> vec_row)
{
	for (int i = 0; i < vec_row.size(); i++)
		cout << vec_row[i] << ' ';
	cout << endl;
}

int main() 
{
	//根据规律，第一行元素最右边是(N^2+N)/2,第二行是第一行元素依次减掉1，再去掉最左边的元素
	int N;
	cin >> N;
	vector<int> first_row;
	for (int i = 1; i <= N; i++) {
		first_row.push_back((i * i + i) / 2);
	}

	for (int row = 1; row <= N; row++) {
		print_row(first_row);
		first_row = renew_row(first_row);
	}

	return 0;
}