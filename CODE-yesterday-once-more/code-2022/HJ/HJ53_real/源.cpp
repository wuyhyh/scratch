//杨辉三角变形

#include <iostream>
#include <vector>
using namespace std;

//杨辉三角规律                                    行号    第一个偶数在该行第几个
//                    1                           1             -1
//                1   1   1                       2             -1
//            1   2   3   2   1                   3              2
//         1  3   6   7   6   3   1               4              3
//      1  4  10  16  19  16  10  4  1            5              2
//   1  5  15 30  45  51  45  30  15 5  1         6              4

//生成三角形再判断奇偶

vector<int> generate_sanjiao(int line)
{
	vector<int> line_n;
	if (line == 1) {
		line_n.push_back(1);
		return line_n;
	}

	vector<int> line_last = generate_sanjiao(line - 1);
	line_last.push_back(0);
	line_last.insert(line_last.begin(), 0);
	line_n.push_back(1);
	for (int i = 1; i <= line_last.size()-2; i++) {
		line_n.push_back(line_last[i - 1] + line_last[i] + line_last[i + 1]);
	}
	line_n.push_back(1);
	return line_n;
}

int first_even(vector<int> vec_int)
{
	int i = 1;
	for (; i <= vec_int.size(); i++) {
		if (vec_int[i-1] % 2 == 0)
			return i;
	}
	return -1;
}

//使用递归可以构造三角形，但是新的问题是运行超时

int main()
{
	int line;
	cin >> line;
	vector<int> jiao = generate_sanjiao(line);
	cout << first_even(jiao) << endl;

	return 0;
}