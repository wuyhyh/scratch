//最大子序列和的问题

//算法1 O(n3)
int max_subseq_sum1(int arr[], int n)
{
	int this_sum;
	int max_sum = 0;
	int i, j, k;
	for (i = 0; i < n; i++) {//i是子序列左端的位置
		for (j = i; j < n; j++) {//j是子序列右端的位置
			this_sum = 0;
			for (k = i; k <= j; k++) {
				this_sum += arr[k];
			}
			if (this_sum > max_sum)//更新结果
				max_sum = this_sum;
		}
	}
	return max_sum;
}

//算法2 O(n2)
//k循环不是必要的
int max_subseq_sum2(int arr[], int n)
{
	int this_sum;
	int max_sum = 0;
	int i, j;
	for (i = 0; i < n; i++) {
		this_sum = 0;//this_sum是arr[i]到arr[j]的和
		for (j = i; j < n; j++) {
			this_sum += arr[j];//对于相同的i，只要在j-1次循环的基础上加1项就行
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
	int max_left_sum;//存放左右问题的解
	int max_right_sum;
	int max_left_border_sum;//存放跨越分界线问题的结果
	int max_right_border_sum;

	int center;

	if (left == right) {//递归的终止条件，子序列只有一个数字
		if (list[left] > 0)
			return list[left];
		else
			return 0;
	}

	//下面是分的过程
	center = (left + right) / 2;
	max_left_sum = divide_conquer(list, left, center);
	max_right_sum = divide_conquer(list, center + 1, right);

	//下面求跨越分界线的和
	int left_border_sum = 0;
	max_left_border_sum = 0;
	for (int i = center; i >= left; i--) {//从中间向左扫描
		left_border_sum += list[i];
		if (max_left_border_sum < left_border_sum)
			max_left_border_sum = left_border_sum;
	}

	int right_border_sum = 0;
	max_right_border_sum = 0;
	for (int i = center+1; i <= right; i++) {//向右扫描
		right_border_sum += list[i];
		if (max_right_border_sum < right_border_sum)
			max_right_border_sum = right_border_sum;
	}

	return max3(max_left_sum, max_right_sum, max_left_border_sum + max_right_border_sum);
}

//算法3 分而治之，采用递归 O(nlogn)
int max_subseq_sum3(int arr[], int n)//进行封装，保证接口一致
{
	return divide_conquer(arr, 0, n - 1);
}

//算法4 在线算法,最快O(n)线性的
int max_subseq_sum4(int arr[], int n)//副作用是，不一定总是正确
{
	int this_sum = 0;
	int max_sum = 0;
	int i;

	for (i = 0; i < n; i++) {
		this_sum += arr[i];//向右累加
		if (this_sum > max_sum)
			max_sum = this_sum;//发现更大的更新结果
		else if (this_sum < 0)//当前子列和为负数，抛弃
			this_sum = 0;//重新开始
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