#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

/*
*
* 排序是将一组对象按某种逻辑顺序重新排列的过程
*
* 基本的排序方法有
*	1.交换排序：冒泡排序->快速排序
*		冒泡排序分为：基本情形和利用falg进行检测的改进版本
*		快速排序最重要的是切分元素pivot的选取，最经典的是三中值median3方法；
*		快速排序在子序列规模减小到某阈值时，切换成插入排序的改进
*		当重复元素较多时，采用三切分的快速排序改进
*	2.插入排序：简单插入排序->折半插入排序->希尔排序
*		希尔排序的增量序列主流有：	折半取下界、
*								Hibbard序列2^k-1、
*								Sedgewick序列9*4^i - 9*2^i+1或者4^i - 3*2^+1
*	3.选择排序：简单选择排序->堆排序，
*		堆排序有两种空间代价，可以是O(N),也可以O(1)，Sedgewick序列的shell_sort可能超过heap_sort
*	4.归并排序：外排序的基础
*		归并排序可以采用递归实现，也可以非递归实现
*		归并排序还分为自底向上的递归和自顶向下的递归
*	5.桶排序->基数排序，
*		桶排序：以空间换时间，与比较操作无关，要求事先已知数据的取值范围；
*		基数排序：推广单关键字的桶排序到多关键字的基数排序，所谓基数就是整数的分解，分为：MSD主位优先；LSD次位优先
*
* 比较树的下界问题：
*	1.交换2个相邻元素可以消除一个逆序对，因此insertion_sort和bubble_sort比较次数是相等的。
*	2.一个N元素的序列，平均逆序对是N*(N-1)/4，因此任何仅交换相邻元素的排序算法下界是Ω(N^2)。
*	3.如果交换非相邻元素就有希望提高效率，因此冒泡排序和插入排序分别发展出了快速排序和希尔排序。
*	4.这种发展带来了一个新的概念，稳定性问题。排序的稳定性是指同义词在排序前后的相对位置不发生变化。
*		稳定的算法有：直接插入排序、冒泡排序、归并排序、基数排序
*		不稳定的算法有：希尔排序、快速排序、简单选择排序、堆排序、
*	5.基于比较的算法的上界是归并排序，严格的O(NlogN);
*
*/

/*
bubble_sort()
insertion_sort()//折半插入
shell_sort()
quick_sort()
merge_sort()
selection_sort()
heap_sort()
bucket_sort()
radix_sort()
*/


typedef int elemtype;

void swap(elemtype* a, elemtype* b)
{
	elemtype temp = *a;
	*a = *b;
	*b = temp;
}

//冒泡排序
/*
* 冒泡排序的规则是：
	1.先考虑数组的N-1个位置，从第0个位置上的元素开始，看看是否其后相邻的元素更小，更小就上浮交换二者
	2.然后再看第1个位置上的元素和它后面的元素要不要交换。
	3.倒数第二个位置的元素和最后一个元素比较并发生可能的交换后一轮扫描结束，这时最大的元素固定到了第N-1个位置
	4.第二轮扫描从第0个位置到N-2个位置，每次扫描会排定一个最大元素，直到只有一个元素。
* 改进的思路是，有时序列已经有序，不再需要扫描，算法可以提前结束。
  用一个flag表示有没有发生过交换，如果一次交换都没有发生过，说明已经有序了，那就提前结束。
*/

void bubble_sort(elemtype arr[], int n)
{
	for (int pos = n - 1; pos >= 0; pos--) {
		for (int i = 0; i < pos; i++) {
			if (arr[i + 1] < arr[i])
				swap(&arr[i], &arr[i + 1]);
		}
	}
}

void bubble_sort1(elemtype arr[], int n)
{
	for (int pos = n - 1; pos >= 0; pos--) {
		bool falg = false;//用来标识有没有发生过交换
		for (int i = 0; i < pos; i++) {
			if (arr[i + 1] < arr[i]) {
				swap(&arr[i], &arr[i + 1]);
				falg = true;
			}	
		}
		if (falg == false)
			break;
	}
}

void bubble_sort_flag(elemtype arr[], int n)
{
	int pos;
	int i;
	bool flag = false;

	for (pos = n - 1; pos >= 0; pos--) {
		flag = false;
		for (i = 0; i < pos; i++) {
			if (arr[i + 1] < arr[i]) {//满足条件的上浮
				swap(&arr[i], &arr[i + 1]);
				flag = true;
			}
		}
		if (flag == false)
			break;
	}
}

//选择排序
/*
* 选择排序的规则是：
	1.找到数组中的最小元素，然后把他和数组的第一个位置上的元素交换；（如果他自己最小就和自己交换）
	2.然后再从剩下的数组中找到最小的元素，和数组的第二个位置上的元素交换；
	3.数组中所有元素都被选取了一次算法结束;
* 选择排序的操作次数是确定的：N(N-1)/2次比较，N次交换，这意味着两个特点：
	1.运行时间和输入的性质完全没有关系，逆序数少的差不多已经有序的序列并不会减少操作时间
	2.数据的移动是最少的，只发生N次交换。
*
*/

void selection_sort(elemtype arr[], int n)
{
	for (int pos = 0; pos < n; pos++) {
		int min = pos;
		for (int i = pos + 1; i < n; i++) {
			if (arr[i] < arr[min])
				min = i;
		}
		swap(&arr[min], &arr[pos]);
	}
}

//插入排序
/*
* 插入排序的规则是：
	*整理牌的时候我们把后面摸得牌插入到一个合适的位置。
	1.当前索引左边的部分是有序部分，但他们的最终位置还不确定，为了给插入的元素留出位置，可能需要移动他们的位置。
	2.当索引到达最右端的时候，排序就完成了。
* 插入排序在输入基本有序时会快很多，表现与输入有很大的关系。
* 插入排序在最好的情况下需要N-1次比较，0次交换；最坏情况要N^2/2次比较和N^2/2次交换；平均是N^2/4次比较和交换
* 插入排序比选择排序要快一点点。
*/

void insertion_sort(elemtype arr[], int n)//这种写法速度最快
{
	for (int pos = 1; pos < n; pos++) {
		if (arr[pos - 1] > arr[pos]) {//看看要不要移动元素
			elemtype temp = arr[pos];
			int i;
			for (i = pos; arr[i - 1] > temp; i--) //移动腾出位置
				arr[i] = arr[i - 1];
			arr[i] = temp;
		}
	}
}

void insertion_sort1(elemtype arr[], int n)
{
	for (int pos = 1; pos < n; pos++) {
		elemtype temp = arr[pos];
		int i;
		for (i = pos; i > 0 && arr[i - 1] > temp; i--) //把arr[pos],插入到arr[pos-1]~arr[0]之中
			arr[i] = arr[i - 1];
		arr[i] = temp;
	}
}

void insertion_sort2(elemtype arr[], int n)//这种写法不移动元素，花费的时间比选择排序还要多一点,但是很好记
{
	for (int pos = 1; pos < n; pos++) {
		for (int i = pos; i > 0 && arr[i - 1] > arr[i]; i--) {
			swap(&arr[i - 1], &arr[i]);
		}
	}
}

//折半插入排序
/*
* 插入排序的一个特点是，索引的左侧是有序的序列，右侧是不会被访问的。
  我们在寻找插入的位置的时候，可以不挨个比较，可以使用二分查找来改进。
*/

void insertion_sort_log2(elemtype arr[], int n)//速度提升不是很快
{
	for (int pos = 1; pos < n; pos++) {
		elemtype temp = arr[pos];//先暂存元素

		int left = 0;
		int right = pos - 1;
		while (left <= right) {
			int middle = left + (right - left) / 2;
			if (arr[middle] > arr[pos])
				right = middle - 1;
			else
				left = middle + 1;
		}

		for (int i = pos; i > right + 1; i--) {//right+1=middle移动元素
			arr[i] = arr[i - 1];
		}
		arr[right + 1] = temp;
	}
}

//希尔排序
/*
* 我们知道排序的本质是消除所有的逆序对，插入排序只涉及交换相邻的元素，这样一次只可能减少1个逆序对；
* 如果交换不相邻的元素，就可能减少不止1个逆序对，排序将更快。
* 希尔排序是对插入排序的改进，将数组分成多个固定间隔的子序列，分别插入排序，然后再逐渐减少间隔。
* 确定间隔的方法有很多中，不同的增量序列可能带来很大的不同：
*/

//增量序列：d = 1/2*(3^k-1)
void shell_sort(elemtype arr[], int n)
{
	int h = 1;
	while (h < n / 3)
		h = 3 * h + 1;

	while (h >= 1) {
		//插入排序
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //把arr[pos],插入到arr[pos-1]~arr[0]之中
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
	for (si = 0; sedgewick[si] >= n; si++)//确保初始增量不大于数组长度
		;

	for (int h = sedgewick[si]; h >= 1; h = sedgewick[++si]) {
		//插入排序
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //把arr[pos],插入到arr[pos-1]~arr[0]之中
				arr[i] = arr[i - h];
			arr[i] = temp;
		}
	}
}

void shell_sort2(elemtype arr[], int n)//比插入排序还慢
{
	int seq[10] = { 0 };
	int h = 1;
	for (int i = 0, j = 1; i < 10; i++, j *= 2)
		seq[i] = j;

	int si;
	for (si = 0; seq[si] >= n; si++)//确保初始增量不大于数组长度
		;

	for (int h = seq[si]; h >= 1; h = seq[++si]) {
		//插入排序
		for (int pos = h; pos < n; pos++) {
			elemtype temp = arr[pos];
			int i;
			for (i = pos; i >= h && arr[i - h] > temp; i -= h) //把arr[pos],插入到arr[pos-1]~arr[0]之中
				arr[i] = arr[i - h];
			arr[i] = temp;
		}
	}
}

//堆排序
/*
* 堆排序是在选择排序上的改进。
* 我们把输入的数组进行建堆，然后逐渐删除最小堆，收集删除的元素得到排序的结果。
* 这种想法的问题是，我们需要一个额外的数组来收集删除的元素再复制回原数组。
* 改进的方法是使用最大堆，删除最大堆以后把删除的元素放到数组的最后一位，只需要一个临时变量暂存一下删除的堆顶元素
*
* 建堆需要O(N),N次删除操作O(NlogN).
*
*/

void sink(int arr[], int n, int k)
{
	while (2 * k + 1 <= n) {
		int i = 2 * k + 1;
		if (i < n && (arr[i] < arr[i + 1]))
			i++;//i指向较大的那个子结点

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

//归并排序
/*
* 归并操作把两个数组合成一个数组。
* 归并排序总能保证对一个数组排序所需时间为O(NlogN),缺点是需要一个O(N)的辅助空间
*
* 最简单的想法是创建一个适当大小的数组，然后把两个输入数组的元素一个个从小到大放入这个大数组中。
* 这样做主要的问题是我们对一个大数组进行排序时，需要很多次归并，每一次归并都需要一个辅助数组，这是很大的代价。
*
* 能不能原地归并呢？
* 我们使用一个辅助数组auxiliary，输入的形式是：arr[left,right],middle = left + (right - left)/2,
  我们把[left,middle]和[middle+1,right]归并到辅助数组aux中,然后再复制回原数组arr.
*
*/

//原地归并的抽象方法，注意，并不能直接用于归并排序，辅助数组aux[]应放到最外面。
void merge(int arr[], int aux[], int left, int right)
{
	int middle = left + (right - left) / 2;
	int i = left;
	int j = middle + 1;

	//把arr[]复制到aux[]中
	for (int k = left; k <= right; k++)
		aux[k] = arr[k];

	//把aux[]的左右两部分归并回arr[]
	for (int k = left; k <= right; k++) {
		if (i > middle)//左半边消耗完了
			arr[k] = aux[j++];
		else if (j > right)//右半边消耗完了
			arr[k] = aux[i++];
		else if (aux[j] < aux[i])//选择小的放入
			arr[k] = aux[j++];
		else
			arr[k] = aux[i++];
	}
}

//归并排序
//自顶向下的归并排序
void m_sort(int arr[], int aux[], int lo, int hi)
{
	if (lo >= hi)//结束条件
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

//自底向上的归并排序
int min_one(int a, int b)
{
	return (a < b) ? a : b;
}

//代码量很小
void merge_sort_BU(int arr[], int n)
{
	int* aux = (int*)malloc(n * sizeof(int));//归并的小数组规模翻倍
	for (int size = 1; size < n; size = size + size) {
		for (int lo = 0; lo < n - size; lo += (size + size)) //妙啊
			merge(arr, aux, lo, min_one(lo + size + size - 1, n - 1));
	}
	free(aux);
}

//快速排序
//K&R中的写法，使用快慢指针
void q_sort(int arr[], int left, int right)
{
	if (left >= right)//递归截止条件
		return;

	int i;
	int last;
	int pivot = left + (right - left) / 2;

	swap(&arr[pivot], &arr[left]);//以最左边的元素作为切分点
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (arr[i] < arr[left]) {//last是慢指针，i是快指针
			last++;//如果i处的元素大于切分元素，i就快速突进
			swap(&arr[i], &arr[last]);//如果i处的元素小于切分元素，那么就可以通知last移动腾出一个交换位置
		}
	}

	//排定切分元素
	swap(&arr[left], &arr[last]);//last标记了切分元素的最终位置，其左侧元素都小于切分元素
	q_sort(arr, left, last - 1);
	q_sort(arr, last + 1, right);
}

void quick_sort(int arr[], int n)
{
	q_sort(arr, 0, n - 1);
}

//快速排序的性能与pivot的选取有关
//选取最左、中间、最右三个元素的中位数作为pivot
int median3(int arr[], int left, int right)
{
	//调整使: arr[left] < arr[center] < arr[right]
	int center = left + (right - left) / 2;
	if (arr[left] > arr[center])
		swap(&arr[left], &arr[center]);
	if (arr[left] > arr[right])
		swap(&arr[left], &arr[right]);
	if (arr[center] > arr[right])
		swap(&arr[center], &arr[right]);

	swap(&arr[right - 1], &arr[center]);//把pivot放到倒数第二个位置
	int pivot = arr[center];
	return pivot;
}

//在数组规模较小时，改为插入排序，陈越写法
void q_sort1(int arr[], int left, int right)
{
	int pivot;
	int cutoff = 50;
	int lo, hi;

	if (cutoff <= (right - left + 1)) {
		pivot = median3(arr, left, right);//这一步结束把pivot放到了倒数第二个位置，并且倒数第一个位置上的元素也大于pivot
		lo = left;
		hi = right - 1;
		while (true) {
			while (arr[++lo] < pivot);
			while (arr[--hi] > pivot);

			if (lo < hi)
				swap(&arr[lo], &arr[hi]);
			else
				break;
		}

		//排定pivot的位置
		swap(&arr[lo], &arr[right - 1]);//pivot放在arr[right-1],lo时pivot的最终位置
		q_sort1(arr, left, lo - 1);
		q_sort1(arr, lo + 1, right);
	}
	else
		insertion_sort(arr + left, right - left + 1);//这里arr + left是递归的需要
}

//sedgewick写法，只进行快速排序
void q_sort2(int arr[], int left, int right)
{
	if (left >= right)//递归截止条件
		return;

	int pivot = median3(arr, left, right);//这一步结束把pivot放到了倒数第二个位置，并且倒数第一个位置上的元素也大于pivot
	int lo = left;
	int hi = right - 1;
	while (true) {
		while (arr[++lo] < pivot);
		while (arr[--hi] > pivot);

		if (lo < hi)
			swap(&arr[lo], &arr[hi]);
		else
			break;
	}

	//排定pivot的位置
	swap(&arr[lo], &arr[right - 1]);//pivot放在arr[right-1],lo时pivot的最终位置
	q_sort2(arr, left, lo - 1);
	q_sort2(arr, lo + 1, right);
}

void q_sort3(int arr[], int left, int right)
{
	int cutoff = 100;
	if (left + cutoff >= right) {//子数组规模较小时改为插入排序
		insertion_sort(arr + left, right - left + 1);
		return;//递归截止条件
	}
		
	int pivot = median3(arr, left, right);//这一步结束把pivot放到了倒数第二个位置，并且倒数第一个位置上的元素也大于pivot
	int lo = left;
	int hi = right - 1;
	while (true) {
		while (arr[++lo] < pivot);
		while (arr[--hi] > pivot);

		if (lo < hi)
			swap(&arr[lo], &arr[hi]);
		else
			break;
	}

	//排定pivot的位置
	swap(&arr[lo], &arr[right - 1]);//pivot放在arr[right-1],lo时pivot的最终位置
	q_sort3(arr, left, lo - 1);
	q_sort3(arr, lo + 1, right);
}

//三向切分快速排序，处理重复元素较多的情况。
/*
* 数组中重复元素较多时，快速排序有希望改进到线性
*/

void q_sort_3way(int arr[], int left, int right)
{
	//printf("Say my name. Heisenberg\n");
	if (right <= left) 
		return;
	
	int less_than = left;
	int greater_than = right;
	int equal = left + 1;

	int standard = arr[left];

	while (equal <= greater_than) {
		if (arr[equal] < standard)
			swap(&arr[equal++], &arr[less_than++]);
		else if (arr[equal] > standard)
			swap(&arr[equal], &arr[greater_than--]);
		else
			equal++;
	}

	q_sort_3way(arr, left, less_than - 1);
	q_sort_3way(arr, greater_than + 1, right);
}

//桶排序和基数排序
/*
* 桶排序要求已知待排序元素的取值范围，比如取值范围在0~M-1,那么就需要M个桶。
* 桶的实现是链表的结点，便于分配和收集这两个操作。
* 基数排序是多关键值得桶排序，比如一个三位整数，百位、十位、个位就是三个基数，需要进行三趟桶排序。
  三趟排序可以重复利用桶，所以空间代价还是O(M).
* 一般地，如果有d个关键字，那么就要进行d趟桶排序，分为主位优先MSD；次位优先LSD。
* 用整理扑克牌做例子，主位是花色，次位是面值，那么LSD效率比MSD要高一点，因为LSD基于分配收集策略，MSD基于分治策略，分别排序再合并结果
* 如果有N个关键字，那么一趟排序就需要N个分配和M个收集，总的时间代价就是O(d*(N+M));
* 基数分解问题：
  如果我们按取值范围来分配桶，那么可能带来巨大的空间浪费，比如对20个不超过三位的整数进行排序，我们需要1000个桶
  如果我们以10为基数把三位整数分解，那么取值范围变成了0~9，只需要分配10个桶，相应的我们需要三趟排序。
  一般地，以R为基数分解，就只需要R个桶。
* 
*/

//实现三位整数的基数排序
#define MAX_digit 4//每个元素最多的关键字数
#define Radix 10

//这是一个bucket
typedef struct Node* ptr_to_Node;
struct Node {
	int key;
	ptr_to_Node next;
};

//bucket头结点
struct head_node {
	ptr_to_Node head;
	ptr_to_Node tail;
};

typedef struct head_node bucket[Radix];

//约定次位D=1，主位D<=MAX_digit
int get_digit(int e, int D)
{
	int i, d;
	for (i = 1; i <= D; i++) {
		d = e % Radix;
		e = e / Radix;
	}
	return d;
}

void LSD_radix_sort(int arr[], int n)
{
	int D, Di, i;
	bucket B;
	ptr_to_Node temp, p, List = NULL;

	for (i = 0; i < Radix; i++)//初始化每个桶为空链表
		B[i].head = B[i].tail = NULL;

	for (i = 0; i < n; i++) {//把arr[]逆序存入List
		temp = (ptr_to_Node)malloc(sizeof(struct Node));
		temp->key = arr[i];
		temp->next = List;
		List = temp;
	}

	//从这里开始排序
	for (D = 1; D <= MAX_digit; D++) {
		//分配过程
		p = List;
		while (p) {
			Di = get_digit(p->key, D);
			temp = p;//从List中摘除
			p = p->next;
			temp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = temp;
			else {
				B[Di].tail->next = temp;
				B[Di].tail = temp;
			}
		}

		//收集过程
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--) {
			if (B[Di].head) {
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL;//清空桶
			}
		}
	}

	for (i = 0; i < n; i++) {//把List放回arr[]并释放空间
		temp = List;
		List = List->next;
		arr[i] = temp->key;
		free(temp);
	}
}

//外部排序
/*
* 将内存分为三部分，两个输入缓存和一个输出缓存
* 败者树与多路归并
*/


int main()
{
	int arr[10000] = { 0 };
	for (int i = 0; i < 10000; i++)
		arr[i] = rand();

	clock_t s1, e1;
	s1 = clock();
	//bubble_sort(arr, 10000);
	//selection_sort(arr, 10000);
	//insertion_sort(arr, 10000);
	//shell_sort(arr, 10000);
	//heap_sort(arr, 10000);
	//merge_sort(arr,10000);
	//merge_sort_BU(arr, 10000);
	//quick_sort(arr, 10000);
	//q_sort1(arr, 0, 10000 - 1);
	//q_sort2(arr, 0, 10000 - 1);
	//q_sort3(arr, 0, 10000 - 1);
	q_sort_3way(arr, 0, 10000 - 1);

	e1 = clock();

	double dur1 = (double)(e1 - s1) / CLOCKS_PER_SEC;

	printf("%f\n\n", dur1);

	for (int i = 0; i < 12; i++)
		printf("%d ", arr[i]);
	printf("\n\n");

	int drr[] = { 12,34,64,59,8,96,65,60,89,55,455,56 };

	for (int i = 0; i < 12; i++)
		printf("%d ", drr[i]);
	printf("\n\n");

	//q_sort_3way(drr, 0, 11);
	bubble_sort1(drr, 12);

	//printf("%d\n", median3(drr, 0, 2));

	for (int i = 0; i < 12; i++)
		printf("%d ", drr[i]);
	printf("\n\n");

	int jrr[10] = { 0,1,512,343,64,125,216,27,8,729 };
	for (int i = 0; i < 10; i++)
		printf("%d ", jrr[i]);
	printf("\n\n");

	LSD_radix_sort(jrr, 10);

	for (int i = 0; i < 10; i++)
		printf("%d ", jrr[i]);
	printf("\n\n");

	return 0;
}