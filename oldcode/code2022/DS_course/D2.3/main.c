//��������Ԫ�ص����ֵ

typedef int elemtype;
elemtype max(elemtype arr[], int n)
{
	elemtype curmax = arr[0];//�ȼ���arr[0]���
	for (int i = 1; i < n; i++) {
		if (arr[i] > curmax)
			curmax = arr[i];
	}
	return curmax;
}