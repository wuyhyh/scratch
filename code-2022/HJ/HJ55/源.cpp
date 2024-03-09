//输出 1到n之间 的与 7 有关数字的个数。
//一个数与7有关是指这个数是 7 的倍数，或者是包含 7 的数字
//（如 17 ，27 ，37 ... 70 ，71 ，72 ，73...）

#include<iostream>
#include<vector>
using namespace std;

int main() 
{
	int n;
	while (cin >> n) {
		int cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			if ((i % 7) == 0) //7的倍数
				cnt++;
			else if ((i % 10) == 7 || (i / 10) % 10 == 7 || (i / 100) % 10 == 7 || (i / 1000) % 10 == 7) 
				cnt++;//其中一位含有7
		}
		cout << cnt << endl;
	}

	return 0;
}