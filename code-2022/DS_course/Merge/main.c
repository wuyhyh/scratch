#include<stdio.h>
#include<stdlib.h>

void merge(int arr[], int aux[], int left, int right)
{
	int middle = left + (right - left) / 2;
	int i = left;
	int j = middle + 1;

	//把arr[]复制到aux[]中
	for (int k = left; k <= right; k++)
		aux[k] = arr[k];

	//把aux[]的左右两部分归并回arr[]
	for (int k = left; k <= right; k++) {
		if (i > middle)//左半边消耗完了
			arr[k] = aux[j++];
		else if (j > right)//右半边消耗完了
			arr[k] = aux[i++];
		else if (aux[j] < aux[i])//选择小的放入
			arr[k] = aux[j++];
		else
			arr[k] = aux[i++];
	}
}

void m_sort(int arr[],int aux[],int lo,int hi)
{
	if (lo >= hi)
		return;

	int mid = lo + (hi - lo) / 2;
	m_sort(arr, aux, lo, mid);
	m_sort(arr, aux, mid + 1, hi);
	merge(arr, aux, lo, hi);
}

void merge_sort(int arr[], int n)
{
	int* aux = (int*)malloc(n * sizeof(int));
	m_sort(arr, aux, 0, n - 1);
	free(aux);
}

int main()
{
	int arr[10000] = { 0};
	for (int i = 0; i < 10000; i++)
		arr[i] = rand() + 1;
	merge_sort(arr, 10000);
	for (int i = 0; i < 100; i++)
		printf("%d \n", arr[i]);

	return 0;
}