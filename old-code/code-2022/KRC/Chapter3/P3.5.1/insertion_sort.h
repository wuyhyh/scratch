#ifndef K_INSERTION_SORT_H

#include "swap.h"

void insertion_sort(int arr[], int n)
{
	int i, j;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0) {
			if (arr[j - 1] > arr[j]) {
				swap(&arr[j - 1], &arr[j]);
			}
			j--;
		}
	}
}

void insertion(int arr[], int n)
{
	int i, j;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0; j--) {
			if (arr[j - 1] > arr[j]) {
				swap(&arr[j - 1], &arr[j]);
			}
		}
	}
}

#define K_INSERTION_SORT_H

#endif //K_INSERTION_SORT_H
