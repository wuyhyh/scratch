#include <iostream>

//使用快慢指针实现快速排序
void qsort(int arr[], int left, int right);
void swap(int arr[], int i, int j);

int main()
{
	std::cout << "Hello, World!" << std::endl;

	int arr[] = { 14, 6, 37, 23, 34, 91, 45 };
	qsort(arr, 0, 6);
	for (int i = 0; i < 7; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}

void qsort(int arr[], int left, int right) //right是闭区间的下标
{
	int i;
	int last;
	if (left >= right) { // 数组中的元素小于2，不执行任何操作
		return;
	}

	swap(arr, left, (left + right) / 2);
	last = left; // 将划分子集的元素移动到arr[0]
	for (i = left + 1; i <= right; i++) { // 划分子集
		if (arr[i] < arr[left]) {
			/* 当快指针探测到逆序的时候，慢指针将进行一次交换和移动 */
			/* 如果是覆盖，那么last++,不覆盖值的话，应该是++last */
			swap(arr, ++last, i);
		}
	}
	swap(arr, left, last); // 恢复划分子集的元素

	qsort(arr, left, last - 1);
	qsort(arr, last + 1, right);
}

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}