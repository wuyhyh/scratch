//计算一个浮点数的立方根，不使用库函数。
//保留一位小数。

#include<iostream>
#include<cmath>
using namespace std;

//牛顿法，不断用一阶泰勒展开近似，直到达到足够的精度

double cube_root(double input)
{
	if (input == 0)//0的立方根直接输出
		return 0;
	double x0 = input;
	double x1 = (2 * x0 + input / (x0 * x0)) / 3;

	while (abs(x1 - x0) > 0.0001) {//没有达到精度就继续迭代
		x0 = x1;
		x1 = (2 * x0 + input / (x0 * x0)) / 3;
	}

	return x1;
}

//使用二分法求立方根，分三种情况考虑，-1，0，1
double binary_root(double input)
{
	double left;
	double right;
	double mid = 0.0;

	left = min(input, -1.0);//涵盖了所有可能性
	right = max(1.0, input);

	while ((right - left) > 0.01) {//利用区间缩小结果的可能范围
		mid = (right + left) / 2;
		if (mid * mid * mid > input) {
			right = mid;
		}
		else if (mid * mid * mid < input) {
			left = mid;
		}
		else {
			return mid;
		}
	}

	return right;
}

int main() 
{
	double num;
	cin >> num;
	printf("%.1f\n", binary_root(num));

	return 0;
}