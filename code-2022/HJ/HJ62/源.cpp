//输入一个正整数，计算它在二进制下的1的个数。

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main() 
{
	int num;
	while (cin >> num) {
		bitset<32> binary(num);//把num表示成32位 放在binary中
		cout << binary.count() << endl;//count()方法输出其中1的个数
	}

	return 0;
}