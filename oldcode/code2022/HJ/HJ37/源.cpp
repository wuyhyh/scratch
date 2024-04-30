//有一种兔子，从出生后第3个月起每个月都生一只兔子，小兔子长到第三个月后每个月又生一只兔子。
//例子：假设一只兔子第3个月出生，那么它第5个月开始会每个月生一只兔子。
//一月的时候有一只兔子，假如兔子都不死，问第n个月的兔子总数为多少？
//数据范围：输入满足 1 \le n \le31 \1≤n≤31

#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

//使用递归的思想，第一个月，第二个月是初始条件，后面的月份的兔子等于 新增加的+之前一个月的兔子

int rabbits(int month)
{
	if (month == 1)
		return 1;
	if (month == 2)
		return 1;

	int last_month = rabbits(month - 1);
	int birth_this_month = rabbits(month - 2);
	return last_month + birth_this_month;
}


int main() 
{
	int month;
	while(cin >> month)
		cout << rabbits(month) << endl;

	return 0;
}
