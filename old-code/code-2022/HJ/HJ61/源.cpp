//把m个同样的苹果放在n个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//把数m分成n份，有多少种分法

//使用递归的思想

//设f(m, n) 为m个苹果，n个盘子的放法数目，则先对n作讨论，
//当n > m：必定有n - m个盘子永远空着，去掉它们对摆放苹果方法数目不产生影响。即if(n > m) f(m, n) = f(m, m)
//当n <= m：不同的放法可以分成两类：
//1、有至少一个盘子空着，即相当于f(m, n) = f(m, n - 1);
//2、所有盘子都有苹果，相当于可以从每个盘子中拿掉一个苹果，不影响不同放法的数目，即f(m, n) = f(m - n, n).
//而总的放苹果的放法数目等于两者的和，即 f(m, n) = f(m, n - 1) + f(m - n, n)
//递归出口条件说明：
//当n = 1时，所有苹果都必须放在一个盘子里，所以返回１；
//当没有苹果可放时，定义为１种放法；
//递归的两条路，第一条n会逐渐减少，终会到达出口n == 1;
//第二条m会逐渐减少，因为n > m时，我们会return f(m, m)　所以终会到达出口m == 0．

int method(int m, int n)
{
	if (m == 0 || n == 1) {//递归结束条件，没有apple或者只有一个disk
		return 1;
	}
	else if (m < n) {//存在空盘，问题转化
		return method(m, m);//空盘对结果毫无影响
	}
	else{//不存在空盘
		return method(m, n - 1) + method(m - n, n);//至少出现一个空盘+所有盘子都至少放一个
	}
}

int main() 
{
	int m;
	int n;
	while (cin >> m >> n) {
		cout << method(m, n) << endl;
	}

	return 0;
}
