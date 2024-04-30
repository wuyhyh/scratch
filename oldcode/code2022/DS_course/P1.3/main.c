//��������к͵�����

//�㷨1 O(n3)
int max_subseq_sum1(int arr[], int n)
{
	int this_sum;
	int max_sum = 0;
	int i, j, k;
	for (i = 0; i < n; i++) {//i����������˵�λ��
		for (j = i; j < n; j++) {//j���������Ҷ˵�λ��
			this_sum = 0;
			for (k = i; k <= j; k++) {
				this_sum += arr[k];
			}
			if (this_sum > max_sum)//���½��
				max_sum = this_sum;
		}
	}
	return max_sum;
}

//�㷨2 O(n2)
//kѭ�����Ǳ�Ҫ��
int max_subseq_sum2(int arr[], int n)
{
	int this_sum;
	int max_sum = 0;
	int i, j;
	for (i = 0; i < n; i++) {
		this_sum = 0;//this_sum��arr[i]��arr[j]�ĺ�
		for (j = i; j < n; j++) {
			this_sum += arr[j];//������ͬ��i��ֻҪ��j-1��ѭ���Ļ����ϼ�1�����
			if (max_sum < this_sum)
				max_sum = this_sum;
		}
	}
	return max_sum;
}

int max3(int a, int b, int c)
{
	if (a > b) 
		return (a > c) ? a : c;
	else 
		return (b > c) ? b : c;
}

int divide_conquer(int list[], int left, int right)
{
	int max_left_sum;//�����������Ľ�
	int max_right_sum;
	int max_left_border_sum;//��ſ�Խ�ֽ�������Ľ��
	int max_right_border_sum;

	int center;

	if (left == right) {//�ݹ����ֹ������������ֻ��һ������
		if (list[left] > 0)
			return list[left];
		else
			return 0;
	}

	//�����ǷֵĹ���
	center = (left + right) / 2;
	max_left_sum = divide_conquer(list, left, center);
	max_right_sum = divide_conquer(list, center + 1, right);

	//�������Խ�ֽ��ߵĺ�
	int left_border_sum = 0;
	max_left_border_sum = 0;
	for (int i = center; i >= left; i--) {//���м�����ɨ��
		left_border_sum += list[i];
		if (max_left_border_sum < left_border_sum)
			max_left_border_sum = left_border_sum;
	}

	int right_border_sum = 0;
	max_right_border_sum = 0;
	for (int i = center+1; i <= right; i++) {//����ɨ��
		right_border_sum += list[i];
		if (max_right_border_sum < right_border_sum)
			max_right_border_sum = right_border_sum;
	}

	return max3(max_left_sum, max_right_sum, max_left_border_sum + max_right_border_sum);
}

//�㷨3 �ֶ���֮�����õݹ� O(nlogn)
int max_subseq_sum3(int arr[], int n)//���з�װ����֤�ӿ�һ��
{
	return divide_conquer(arr, 0, n - 1);
}

//�㷨4 �����㷨,���O(n)���Ե�
int max_subseq_sum4(int arr[], int n)//�������ǣ���һ��������ȷ
{
	int this_sum = 0;
	int max_sum = 0;
	int i;

	for (i = 0; i < n; i++) {
		this_sum += arr[i];//�����ۼ�
		if (this_sum > max_sum)
			max_sum = this_sum;//���ָ���ĸ��½��
		else if (this_sum < 0)//��ǰ���к�Ϊ����������
			this_sum = 0;//���¿�ʼ
	}

	return max_sum;
}

#include<stdio.h>
int main()
{
	int arr[8] = { 4, -3,5,-2,-1,2,6,-2 };

	printf("%d\n", max_subseq_sum1(arr,8));
	printf("%d\n", max_subseq_sum2(arr, 8));
	printf("%d\n", max_subseq_sum3(arr, 8));
	printf("%d\n", max_subseq_sum4(arr, 8));

	return 0;
}