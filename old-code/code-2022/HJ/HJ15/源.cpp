//输入一个 int 型的正整数，计算出该 int 型数据在内存中存储时 1 的个数。
//
//数据范围：保证在 32 位整型数字范围内

#include<bitset>
#include<iostream>
using namespace std;

int main() 
{
	int num;
	cin >> num;
	bitset<32> b(num);//用num初始化一个32位长度的位组合
	cout << b.count();//输出零的个数

	return 0;
}