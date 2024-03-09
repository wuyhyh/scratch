//基于排序的方法求中位数

#include<stdio.h>

typedef int elemtype;

elemtype median(elemtype arr[], int n, void (*sort)(elemtype arr[], int n))
{
	sort(arr, n);
	return arr[(n - 1) / 2];
}

void swap(elemtype arr[], int i, int j) {
	elemtype temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void selection(elemtype arr[], int n)
{
	int max_position;

	for (int i = 0; i < n; i++) {
		max_position = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] > arr[max_position])
				swap(arr, max_position, j);
		}
	}
}

void print_arr(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
}


int main()
{
	int arr[] = { 2,4,647,86,6,5,3,3,5,7 };
	selection(arr, 10);
	print_arr(arr, 10);
	printf("median = %d\n", median(arr, 10, &selection));

	return 0;
}