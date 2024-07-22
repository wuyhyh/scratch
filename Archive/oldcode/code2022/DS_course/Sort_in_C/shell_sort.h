#pragma once
#include"data_type.h"

//ϣ������
/*
* ����֪������ı������������е�����ԣ���������ֻ�漰�������ڵ�Ԫ�أ�����һ��ֻ���ܼ���1������ԣ�
* ������������ڵ�Ԫ�أ��Ϳ��ܼ��ٲ�ֹ1������ԣ����򽫸��졣
* ϣ�������ǶԲ�������ĸĽ���������ֳɶ���̶�����������У��ֱ��������Ȼ�����𽥼��ټ����
* ȷ������ķ����кܶ��У���ͬ���������п��ܴ����ܴ�Ĳ�ͬ��
*/

//�������У�d = 1/2*(3^k-1)
void shell_sort(elemtype arr[], int n)
{
	int h = 1;
	while (h < n / 3)
		h = 3 * h + 1;

	while (h >= 1) {
		//��������
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //��arr[pos],���뵽arr[pos-1]~arr[0]֮��
				arr[i] = arr[i - h];
			arr[i] = temp;
		}

		h = h / 3;
	}
}

void shell_sort1(elemtype arr[], int n)
{
	int sedgewick[] = { 929,505,209,109,41,19,5,1 };
	int si;
	for (si = 0; sedgewick[si] >= n; si++)//ȷ����ʼ�������������鳤��
		;

	for (int h = sedgewick[si]; h >= 1; h = sedgewick[++si]) {
		//��������
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //��arr[pos],���뵽arr[pos-1]~arr[0]֮��
				arr[i] = arr[i - h];
			arr[i] = temp;
		}
	}
}

void shell_sort2(elemtype arr[], int n)//�Ȳ���������
{
	int seq[10] = { 0 };
	int h = 1;
	for (int i = 0, j = 1; i < 10; i++, j *= 2)
		seq[i] = j;

	int si;
	for (si = 0; seq[si] >= n; si++)//ȷ����ʼ�������������鳤��
		;

	for (int h = seq[si]; h >= 1; h = seq[++si]) {
		//��������
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //��arr[pos],���뵽arr[pos-1]~arr[0]֮��
				arr[i] = arr[i - h];
			arr[i] = temp;
		}
	}
}
