//验证尼科彻斯定理，即：任何一个整数m的立方都可以写成m个连续奇数之和。
//
//例如：
//1 ^ 3 = 1
//2 ^ 3 = 3 + 5
//3 ^ 3 = 7 + 9 + 11
//4 ^ 3 = 13 + 15 + 17 + 19


#include <iostream>
#include <string>
#include <vector>
using namespace std;

string divide_cube(int m)
{
	int first_of_sequence = m * m - m + 1;
	vector<int> sequence;
	for (int i = 0; i < 2*m; i += 2) {
		sequence.push_back(first_of_sequence + i);
	}
	string result;
	for (int i = 0; i < sequence.size()-1; i++) {
		string temp = to_string(sequence[i]) + '+';
		result += temp;
	}
	result += to_string(*(sequence.end()-1));

	return result;
}



int main()
{
	int m;
	while (cin >> m) {
		cout << divide_cube(m) << endl;
	}

	return 0;
}