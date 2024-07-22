//描述
//功能 : 输入一个正整数，按照从小到大的顺序输出它的所有质因子（重复的也要列举）（如180的质因子为2 2 3 3 5 ）

#include<iostream>
#include <math.h>
using namespace std;

int main() 
{
	int num;
	while (cin >> num) {
		for (int prim = 2; prim <= sqrt(num); prim++) {
			while (num % prim == 0) {
				cout << prim << ' ';
				num = num / prim;
			}
		}
		if (num > 1)//剩下的部分大于1才输出，或者本身是质数从这里输出
			cout << num << ' ';
	}

	return 0;
}