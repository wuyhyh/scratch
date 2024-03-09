#include<stdio.h>
#include<stdbool.h>

typedef int elemtype;
void swap(elemtype* a, elemtype* b)
{
	elemtype temp = *a;
	*a = *b;
	*b = temp;
}

elemtype find_kth_largest(elemtype arr[], int k, int left, int right)
{
	elemtype e = arr[left];//ȡ�����Ϊ�ָ�Ԫ��
	int L = left;
	int R = right;

	while (1) {//��δ�����ǿ��ŵ��з�
		while ((left <= right) && (e >= arr[left]))left++;
		while ((left < right) && (e < arr[right]))right--;
		if (left < right)
			swap(&arr[left], &arr[right]);
		else
			break;
	}

	swap(&arr[left - 1], &arr[L]);//e����left-1��

	if ((left - 1 - L) >= k) {
		return find_kth_largest(arr, k, L, left - 2);
	}
	else if ((left - 1 - L) < k - 1) {
		return find_kth_largest(arr, k - (left - 1 - L) - 1/*��ȥ��һ�������еĸ���*/, left, R);
	}
	else {
		return e;
	}
}

elemtype median(elemtype arr[], int n)
{
	return find_kth_largest(arr, (n + 1) / 2, 0, n - 1);
}

int main()
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	printf("%d\n", median(arr, 10));

	return 0;
}