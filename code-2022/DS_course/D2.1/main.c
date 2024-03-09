//求数组元素的平均数例程

typedef double elemtype;
elemtype average(elemtype arr[], int n)
{
	elemtype sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum / n;
}

#include<stdio.h>

int main()
{
	elemtype arr[] = { 12, 2,1 };
	printf("avr = %.2f\n", average(arr, 3));

	return 0;
}