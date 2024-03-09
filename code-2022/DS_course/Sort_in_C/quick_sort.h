#pragma once
#include"data_type.h"
#include"primary_sort.h"

//��������
//K&R�е�д����ʹ�ÿ���ָ��
void q_sort(int arr[], int left, int right)
{
	if (left >= right)//�ݹ��ֹ����
		return;

	int i;
	int last;
	int pivot = left + (right - left) / 2;

	swap(&arr[pivot], &arr[left]);//������ߵ�Ԫ����Ϊ�зֵ�
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (arr[i] < arr[left]) {//last����ָ�룬i�ǿ�ָ��
			last++;//���i����Ԫ�ش����з�Ԫ�أ�i�Ϳ���ͻ��
			swap(&arr[i], &arr[last]);//���i����Ԫ��С���з�Ԫ�أ���ô�Ϳ���֪ͨlast�ƶ��ڳ�һ������λ��
		}
	}

	//�Ŷ��з�Ԫ��
	swap(&arr[left], &arr[last]);//last������з�Ԫ�ص�����λ�ã������Ԫ�ض�С���з�Ԫ��
	q_sort(arr, left, last - 1);
	q_sort(arr, last + 1, right);
}

void quick_sort(int arr[], int n)
{
	q_sort(arr, 0, n - 1);
}

//���������������pivot��ѡȡ�й�
//ѡȡ�����м䡢��������Ԫ�ص���λ����Ϊpivot
int median3(int arr[], int left, int right)
{
	//����ʹ: arr[left] < arr[center] < arr[right]
	int center = left + (right - left) / 2;
	if (arr[left] > arr[center])
		swap(&arr[left], &arr[center]);
	if (arr[left] > arr[right])
		swap(&arr[left], &arr[right]);
	if (arr[center] > arr[right])
		swap(&arr[center], &arr[right]);

	swap(&arr[right - 1], &arr[center]);//��pivot�ŵ������ڶ���λ��
	int pivot = arr[center];
	return pivot;
}

//�������ģ��Сʱ����Ϊ�������򣬳�Խд��
void q_sort1(int arr[], int left, int right)
{
	int pivot;
	int cutoff = 50;
	int lo, hi;

	if (cutoff <= (right - left + 1)) {
		pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
		lo = left;
		hi = right - 1;
		while (true) {
			while (arr[++lo] < pivot);
			while (arr[--hi] > pivot);

			if (lo < hi)
				swap(&arr[lo], &arr[hi]);
			else
				break;
		}

		//�Ŷ�pivot��λ��
		swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
		q_sort1(arr, left, lo - 1);
		q_sort1(arr, lo + 1, right);
	}
	else
		insertion_sort(arr + left, right - left + 1);//����arr + left�ǵݹ����Ҫ
}

//sedgewickд����ֻ���п�������
void q_sort2(int arr[], int left, int right)
{
	if (left >= right)//�ݹ��ֹ����
		return;

	int pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
	int lo = left;
	int hi = right - 1;
	while (true) {
		while (arr[++lo] < pivot);
		while (arr[--hi] > pivot);

		if (lo < hi)
			swap(&arr[lo], &arr[hi]);
		else
			break;
	}

	//�Ŷ�pivot��λ��
	swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
	q_sort2(arr, left, lo - 1);
	q_sort2(arr, lo + 1, right);
}

void q_sort3(int arr[], int left, int right)
{
	int cutoff = 100;
	if (left + cutoff >= right) {//�������ģ��Сʱ��Ϊ��������
		insertion_sort(arr + left, right - left + 1);
		return;//�ݹ��ֹ����
	}

	int pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
	int lo = left;
	int hi = right - 1;
	while (true) {
		while (arr[++lo] < pivot);
		while (arr[--hi] > pivot);

		if (lo < hi)
			swap(&arr[lo], &arr[hi]);
		else
			break;
	}

	//�Ŷ�pivot��λ��
	swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
	q_sort3(arr, left, lo - 1);
	q_sort3(arr, lo + 1, right);
}

//�����зֿ������򣬴����ظ�Ԫ�ؽ϶�������
/*
* �������ظ�Ԫ�ؽ϶�ʱ������������ϣ���Ľ�������
*/

void q_sort_3way(int arr[], int left, int right)
{
	//printf("Say my name. Heisenberg\n");
	if (right <= left)
		return;

	int less_than = left;
	int greater_than = right;
	int equal = left + 1;

	int standard = arr[left];

	while (equal <= greater_than) {
		if (arr[equal] < standard)
			swap(&arr[equal++], &arr[less_than++]);
		else if (arr[equal] > standard)
			swap(&arr[equal], &arr[greater_than--]);
		else
			equal++;
	}

	q_sort_3way(arr, left, less_than - 1);
	q_sort_3way(arr, greater_than + 1, right);
}
