#pragma once
#include"data_type.h"

//������
/*
* ����������ѡ�������ϵĸĽ���
* ���ǰ������������н��ѣ�Ȼ����ɾ����С�ѣ��ռ�ɾ����Ԫ�صõ�����Ľ����
* �����뷨�������ǣ�������Ҫһ��������������ռ�ɾ����Ԫ���ٸ��ƻ�ԭ���顣
* �Ľ��ķ�����ʹ�����ѣ�ɾ�������Ժ��ɾ����Ԫ�طŵ���������һλ��ֻ��Ҫһ����ʱ�����ݴ�һ��ɾ���ĶѶ�Ԫ��
*
* ������ҪO(N),N��ɾ������O(NlogN).
*
*/

void sink(int arr[], int n, int k)
{
	while (2 * k + 1 <= n) {
		int i = 2 * k + 1;
		if (i < n && (arr[i] < arr[i + 1]))
			i++;//iָ��ϴ���Ǹ��ӽ��

		if (arr[i] < arr[k])
			break;
		else
			swap(&arr[i], &arr[k]);
		k = i;
	}
}

void heap_sort(int arr[], int n)
{
	int size = n - 1;
	for (int k = size / 2 - 1; k >= 0; k--)
		sink(arr, size, k);

	while (size > 0) {
		swap(&arr[0], &arr[size]);
		size--;
		sink(arr, size, 0);
	}
}
