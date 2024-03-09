//某商店规定：三个空汽水瓶可以换一瓶汽水，允许向老板借空汽水瓶（但是必须要归还）。
//小张手上有n个空汽水瓶，她想知道自己最多可以喝到多少瓶汽水。
//数据范围：输入的正整数满足 1 \le n \le 100 \1≤n≤100
//
//注意：本题存在多组输入。输入的 0 表示输入结束，并不用输出结果。

//这是一个递归问题
//也可以理解成数论问题
#include<iostream>
using namespace std;

void kidding(int num)
{

	cout << num / 2 << endl;

}

#define SWAP 3
int recursive(int empty_bottle)
{
	if (empty_bottle == SWAP - 1) {//两瓶就交换
		return 1;
	}
	else if (empty_bottle < SWAP - 1) {//少于两瓶结束
		return 0;
	}

	//准备开始喝
	int rest = 0;
	int drinked = 0;
	drinked = empty_bottle / SWAP;
	rest = drinked + empty_bottle % SWAP;

	return drinked + recursive(rest);//注意返回的是总的喝掉的瓶子数
}


int main()
{
	int num;
	while (cin >> num && num != 0) {
		cout << recursive(num) << endl;
		//kidding(num);
	}

	return 0;
}