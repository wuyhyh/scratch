#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

/*
* �ѣ�����Ҫ����2��������
* ɾ�����Ԫ�ء�����Ԫ��
* 
* �ѵĲ������ܻ��ƻ��ѵĽṹ�����±����ѻָ��ѵĽṹ�����ѵ�����
* �ѵ����������֣�
	һ����Ԫ�ص����ȼ���������Ҫ���¶��ϻָ��ѵ������ԣ������ڶѵ�ĩβ����һ�������Ԫ�ص��ϸ���
	һ����Ԫ�ص����ȼ��½�����Ҫ���϶��»ָ��ѵ������ԣ���������Ѷ�Ԫ��Ϊһ��СԪ�غ���³���
* 


*/

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swim(int arr[],int k)
{
	while (k > 1 && (arr[k / 2] < arr[k])) {
		swap(&arr[k / 2], &arr[k]);
		k = k / 2;
	}
}

void sink(int arr[],int n, int k)
{
	while (2 * k <= n) {
		int i = 2 * k;
		if (i < n && (arr[i] < arr[i+1]))
			i++;//iָ��ϴ���Ǹ��ӽ��

		if (arr[i] < arr[k])
			break;
		else
			swap(&arr[i], &arr[k]);
		k = i;
	}
}

typedef struct Hnode{
	int* data;
	int size;
	int maxsize;
}*Heap;

Heap create_heap(int maxsize)
{
	Heap H = (Heap)malloc(sizeof(struct Hnode));
	H->data = (int*)malloc((maxsize + 1)*sizeof(int));
	H->maxsize = maxsize;
	H->size = 0;
	return H;
}

void insert(Heap H, int e)
{
	H->data[++H->size] = e;
	swim(H->data, H->size);
}

int del_max(Heap H)
{
	int max = H->data[1];
	swap(&H->data[H->size], &H->data[1]);
	H->data[H->size] = NULL;
	H->size--;
	sink(H->data,H->size,1);
	return max;
}

void heap_sort(int arr[], int n)
{
	int* brr = (int*)malloc((n + 1) * sizeof(int));
	for (int i = 1; i <= n; i++)
		brr[i] = arr[i - 1];

	for (int k = n / 2; k >= 1; k--) 
		sink(brr, n, k);

	int nn = n;

	while (n > 1) {
		swap(&brr[1], &brr[n]);
		n--;
		sink(brr, n, 1);
	}

	for (int i = 1; i <= nn; i++)
		arr[i-1] = brr[i];
	free(brr);
}

void heap_sort2(int arr[], int n)
{
	int cnt = n - 1;
	for (int k = cnt / 2; k >= 1; k--)
		sink(arr, cnt, k);

	while (cnt > 1) {
		swap(&arr[1], &arr[cnt]);
		cnt--;
		sink(arr, cnt, 1);
	}
	
	int min = arr[1];
	if (arr[0] < min)
		return;
	else {
		swap(&arr[1], &arr[0]);

		cnt = n - 1;
		for (int k = cnt / 2; k >= 1; k--)
			sink(arr, cnt, k);

		while (cnt > 1) {
			swap(&arr[1], &arr[cnt]);
			cnt--;
			sink(arr, cnt, 1);
		}

	}
}

void sink2(int arr[], int n, int k)
{
	while (2 * k+1 <= n) {
		int i = 2 * k+1;
		if (i < n && (arr[i] < arr[i + 1]))
			i++;//iָ��ϴ���Ǹ��ӽ��

		if (arr[i] < arr[k])
			break;
		else
			swap(&arr[i], &arr[k]);
		k = i;
	}
}

void heap_sort3(int arr[], int n)
{
	int size = n - 1;
	for (int k = size / 2-1; k >= 0; k--)
		sink2(arr, size, k);

	while (size > 0) {
		swap(&arr[0], &arr[size]);
		size--;
		sink2(arr, size, 0);
	}
}


int main()
{
	//Heap ss = create_heap(20);
	//for(int i=0;i<10;i++)
	//	insert(ss, rand() % 300);

	//printf("%d\n\n", ss->size);

	//for (int i = 0; i < 10; i++)
	//	printf("%d \n", del_max(ss));

	//for(int i=1;i<=ss->size;i++)
	//	printf("%d\n", ss->data[i]);

	int arr[] = { 12,3,435,670,7,8,987,90 };
	for(int i=0;i<8;i++)
		printf("%d ", arr[i]);
	putchar('\n');

	heap_sort3(arr, 8);

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);

	return 0;
}

