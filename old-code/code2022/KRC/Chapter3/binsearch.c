#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void isort(int arr[], int n)
{
	int i, j;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0) {
			if (arr[j - 1] > arr[j])
				swap(&arr[j - 1], &arr[j]);
			j--;
		}
	}
}

int *rand_n(int max, int n)
{
	int *temp = (int *)malloc(n * sizeof(*temp));
	for (int i = 0; i < n; i++) {
		temp[i] = rand() % max + 1;
	}
	isort(temp, n);
	return temp;
}

void show(int *temp, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", temp[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}
}

int bin_search(int arr[], int n, int target)
{
	int left = 0;
	int right = n - 1;

	while (left <= right) {
		int middle = left + (right - left) / 2;
		if (target > arr[middle]) {
			left = middle + 1;
		} else if (target < arr[middle]) {
			right = middle - 1;
		} else {
			return middle;
		}
	}

	return -1;
}

#define MAX 100
#define N 40

int main()
{
	int *ss = rand_n(MAX, N);
	show(ss, N);
	int target = ss[rand() % N];
	printf("find %d at %d\n", target, bin_search(ss, N, target));
	return 0;
}
