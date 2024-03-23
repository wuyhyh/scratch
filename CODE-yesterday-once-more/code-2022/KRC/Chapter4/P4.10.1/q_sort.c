#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void q_sort(int arr[], int left, int right)
{
	if (left >= right) //数组中已经没有元素了
		return;

	int i, last;
	int partition = (left + right) / 2; //取中间的作为切分元素
	swap(&arr[left], &arr[partition]); //将切分元素暂时放到最左边

	//双指针法，last作为慢指针，i作为快指针，last左侧的元素都小于切分元素
	last = left; //last将是切分元素的最终位置
	for (i = left + 1; i <= right;
		 i++) { //扫描整个数组，i会在大于切分元素的位置快速突进
		if (arr[i] < arr[left]) { //i在前方发现了一个小于切分元素的值
			last++; //last移动到i走过的地方，这个地方的值是切分元素的
			swap(&arr[i],
				 &arr[last]); //交换保证了last现在位置和所处位置小于等于切分元素
		}
	}

	swap(&arr[left], &arr[last]); //排定切分元素
	q_sort(arr, left, last - 1); //左侧排序
	q_sort(arr, last + 1, right); //右侧排序
}

int *rand_int(int n, int max)
{
	int *temp = (int *)malloc(n * sizeof(*temp));
	for (int i = 0; i < n; i++) {
		temp[i] = rand() % max + 1;
	}
	return temp;
}

void print_int(int arr[], int n, int gap)
{
	for (int i = 0; i < n; i += gap) {
		printf("%d ", arr[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}
}

int main()
{
	int *ss = rand_int(10000, 20000);
	print_int(ss, 10000, 100);
	printf("\n\n\n\n");
	q_sort(ss, 0, 9999);
	print_int(ss, 10000, 100);

	return 0;
}
