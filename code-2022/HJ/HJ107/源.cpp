//����һ��������������������ʹ�ÿ⺯����
//����һλС����

#include<iostream>
#include<cmath>
using namespace std;

//ţ�ٷ���������һ��̩��չ�����ƣ�ֱ���ﵽ�㹻�ľ���

double cube_root(double input)
{
	if (input == 0)//0��������ֱ�����
		return 0;
	double x0 = input;
	double x1 = (2 * x0 + input / (x0 * x0)) / 3;

	while (abs(x1 - x0) > 0.0001) {//û�дﵽ���Ⱦͼ�������
		x0 = x1;
		x1 = (2 * x0 + input / (x0 * x0)) / 3;
	}

	return x1;
}

//ʹ�ö��ַ�����������������������ǣ�-1��0��1
double binary_root(double input)
{
	double left;
	double right;
	double mid = 0.0;

	left = min(input, -1.0);//���������п�����
	right = max(1.0, input);

	while ((right - left) > 0.01) {//����������С����Ŀ��ܷ�Χ
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