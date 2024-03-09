#ifndef K_SORT_H

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertion_sort(int arr[], int n)
{
	int i, j;

	for (i = 1; i < n; i++) { //将a[i]插入到a[i-1]--a[0]之间
		for (j = i; j > 0; j--) {
			if (arr[j - 1] > arr[j])
				swap(&arr[j - 1], &arr[j]);
		}
	}
}

void selection_sort(int arr[], int n)
{
	int i, j, min;

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i; j < n; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		swap(&arr[i], &arr[min]);
	}
}

enum boolean { false, true };
int partion(int arr[], int low, int high)
{
	int key = arr[low];
	int i = low;
	int j = high;

	while (true) {
		while (arr[i++] <= key) {
			if (i == high)
				break;
		}
		while (arr[j--] >= key) {
			if (j == low)
				break;
		}
		if (i >= j) {
			break;
		} else {
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[low], &arr[j]);
	return j;
}

void quick_sort(int arr[], int low, int high)
{
	int pos = partion(arr, low, high);
	if (low < high) {
		quick_sort(arr, low, pos - 1);
		quick_sort(arr, pos + 1, high);
	}
}

#define K_SORT_H

#endif //K_SORT_H
