//求数组中元素的最大值

typedef int elemtype;
elemtype max(elemtype arr[], int n)
{
	elemtype curmax = arr[0];//先假设arr[0]最大
	for (int i = 1; i < n; i++) {
		if (arr[i] > curmax)
			curmax = arr[i];
	}
	return curmax;
}