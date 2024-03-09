#include <stdio.h>
#include "rand_number.h"
#include "show_array.h"
#include "insertion_sort.h"
#include "swap.h"

#define MAX 100
#define N 30

void shell_sort(int arr[], int n)
{
	int i, j, gap;

	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			for (j = i - gap; j >= 0; j -= gap) {
				if (arr[j] > arr[j + gap])
					swap(&arr[j], &arr[j + gap]);
			}
		}
	}
}

void shell(int arr[], int n)
{
	int i, j, gap;

	for (gap = n / 2; gap > 0; gap = gap / 2) { //分为gap个子序列\
		子序列逐渐减小为1个
		for (i = gap; i < n; i++) { //以gap为间隔的插入排序
			for (j = i - gap; j >= 0; j = j - gap) {
				if (arr[j] > arr[j + gap]) {
					swap(&arr[j], &arr[j + gap]);
				}
			}
		}
	}
}

void select(int arr[], int n)
{
	int i, j, min;

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap(&arr[i], &arr[min]);
	}
}

int main()
{
	int *ss = rand_n(MAX, N);
	show(ss, N);
	//insertion_sort(ss, N);
	//shell_sort(ss, N);
	//shell(ss, N);
	//insertion(ss, N);
	select(ss, N);
	show(ss, N);

	return 0;
}
