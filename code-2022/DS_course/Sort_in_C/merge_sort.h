#pragma once
#include"data_type.h"

//�鲢����
/*
* �鲢��������������ϳ�һ�����顣
* �鲢�������ܱ�֤��һ��������������ʱ��ΪO(NlogN),ȱ������Ҫһ��O(N)�ĸ����ռ�
*
* ��򵥵��뷨�Ǵ���һ���ʵ���С�����飬Ȼ����������������Ԫ��һ������С�����������������С�
* ��������Ҫ�����������Ƕ�һ���������������ʱ����Ҫ�ܶ�ι鲢��ÿһ�ι鲢����Ҫһ���������飬���Ǻܴ�Ĵ��ۡ�
*
* �ܲ���ԭ�ع鲢�أ�
* ����ʹ��һ����������auxiliary���������ʽ�ǣ�arr[left,right],middle = left + (right - left)/2,
  ���ǰ�[left,middle]��[middle+1,right]�鲢����������aux��,Ȼ���ٸ��ƻ�ԭ����arr.
*
*/

//ԭ�ع鲢�ĳ��󷽷���ע�⣬������ֱ�����ڹ鲢���򣬸�������aux[]Ӧ�ŵ������档
void merge(int arr[], int aux[], int left, int right)
{
	int middle = left + (right - left) / 2;
	int i = left;
	int j = middle + 1;

	//��arr[]���Ƶ�aux[]��
	for (int k = left; k <= right; k++)
		aux[k] = arr[k];

	//��aux[]�����������ֹ鲢��arr[]
	for (int k = left; k <= right; k++) {
		if (i > middle)//������������
			arr[k] = aux[j++];
		else if (j > right)//�Ұ����������
			arr[k] = aux[i++];
		else if (aux[j] < aux[i])//ѡ��С�ķ���
			arr[k] = aux[j++];
		else
			arr[k] = aux[i++];
	}
}

//�鲢����
//�Զ����µĹ鲢����
void m_sort(int arr[], int aux[], int lo, int hi)
{
	if (lo >= hi)//��������
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

//�Ե����ϵĹ鲢����
int min_one(int a, int b)
{
	return (a < b) ? a : b;
}

//��������С
void merge_sort_BU(int arr[], int n)
{
	int* aux = (int*)malloc(n * sizeof(int));//�鲢��С�����ģ����
	for (int size = 1; size < n; size = size + size) {
		for (int lo = 0; lo < n - size; lo += (size + size)) //�
			merge(arr, aux, lo, min_one(lo + size + size - 1, n - 1));
	}
	free(aux);
}
