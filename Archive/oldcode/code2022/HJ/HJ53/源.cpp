//杨辉三角变形

#include <iostream>
using namespace std;

//杨辉三角规律                                    行号    第一个偶数在该行第几个
//                    1                           1             -1
//                1   1   1                       2             -1
//            1   2   3   2   1                   3              2
//         1  3   6   7   6   3   1               4              3
//      1  4  10  16  19  16  10  4  1            5              2
//   1  5  15 30  45  51  45  30  15 5  1         6              4
//
//  首个偶数在该行第几个的规律： -1 -1 （2 3 2 4）···（2 3 2 4）

//利用2342规律输出结果

int sanjiao(int line)
{
	if (line < 3)
		return -1;
	else if ((line - 2) % 4 == 1)
		return 2;
	else if ((line - 2) % 4 == 2)
		return 3;
	else if ((line - 2) % 4 == 3)
		return 2;
	else//最后用else,避免所有路径失败的情况
		return 4;
}

int main()
{
	int line;
	cin >> line;
	cout << sanjiao(line) << endl;

	return 0;
}

