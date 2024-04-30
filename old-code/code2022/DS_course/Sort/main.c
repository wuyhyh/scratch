#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

/*
*
* �����ǽ�һ�����ĳ���߼�˳���������еĹ���
*
* ���������򷽷���
*	1.��������ð������->��������
*		ð�������Ϊ���������κ�����falg���м��ĸĽ��汾
*		������������Ҫ�����з�Ԫ��pivot��ѡȡ������������ֵmedian3������
*		���������������й�ģ��С��ĳ��ֵʱ���л��ɲ�������ĸĽ�
*		���ظ�Ԫ�ؽ϶�ʱ���������зֵĿ�������Ľ�
*	2.�������򣺼򵥲�������->�۰��������->ϣ������
*		ϣ��������������������У�	�۰�ȡ�½硢
*								Hibbard����2^k-1��
*								Sedgewick����9*4^i - 9*2^i+1����4^i - 3*2^+1
*	3.ѡ�����򣺼�ѡ������->������
*		�����������ֿռ���ۣ�������O(N),Ҳ����O(1)��Sedgewick���е�shell_sort���ܳ���heap_sort
*	4.�鲢����������Ļ���
*		�鲢������Բ��õݹ�ʵ�֣�Ҳ���Էǵݹ�ʵ��
*		�鲢���򻹷�Ϊ�Ե����ϵĵݹ���Զ����µĵݹ�
*	5.Ͱ����->��������
*		Ͱ�����Կռ任ʱ�䣬��Ƚϲ����޹أ�Ҫ��������֪���ݵ�ȡֵ��Χ��
*		���������ƹ㵥�ؼ��ֵ�Ͱ���򵽶�ؼ��ֵĻ���������ν�������������ķֽ⣬��Ϊ��MSD��λ���ȣ�LSD��λ����
*
* �Ƚ������½����⣺
*	1.����2������Ԫ�ؿ�������һ������ԣ����insertion_sort��bubble_sort�Ƚϴ�������ȵġ�
*	2.һ��NԪ�ص����У�ƽ���������N*(N-1)/4������κν���������Ԫ�ص������㷨�½��Ǧ�(N^2)��
*	3.�������������Ԫ�ؾ���ϣ�����Ч�ʣ����ð������Ͳ�������ֱ�չ���˿��������ϣ������
*	4.���ַ�չ������һ���µĸ���ȶ������⡣������ȶ�����ָͬ���������ǰ������λ�ò������仯��
*		�ȶ����㷨�У�ֱ�Ӳ�������ð�����򡢹鲢���򡢻�������
*		���ȶ����㷨�У�ϣ�����򡢿������򡢼�ѡ�����򡢶�����
*	5.���ڱȽϵ��㷨���Ͻ��ǹ鲢�����ϸ��O(NlogN);
*
*/

/*
bubble_sort()
insertion_sort()//�۰����
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

//ð������
/*
* ð������Ĺ����ǣ�
	1.�ȿ��������N-1��λ�ã��ӵ�0��λ���ϵ�Ԫ�ؿ�ʼ�������Ƿ�������ڵ�Ԫ�ظ�С����С���ϸ���������
	2.Ȼ���ٿ���1��λ���ϵ�Ԫ�غ��������Ԫ��Ҫ��Ҫ������
	3.�����ڶ���λ�õ�Ԫ�غ����һ��Ԫ�رȽϲ��������ܵĽ�����һ��ɨ���������ʱ����Ԫ�ع̶����˵�N-1��λ��
	4.�ڶ���ɨ��ӵ�0��λ�õ�N-2��λ�ã�ÿ��ɨ����Ŷ�һ�����Ԫ�أ�ֱ��ֻ��һ��Ԫ�ء�
* �Ľ���˼·�ǣ���ʱ�����Ѿ����򣬲�����Ҫɨ�裬�㷨������ǰ������
  ��һ��flag��ʾ��û�з��������������һ�ν�����û�з�������˵���Ѿ������ˣ��Ǿ���ǰ������
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
		bool falg = false;//������ʶ��û�з���������
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
			if (arr[i + 1] < arr[i]) {//�����������ϸ�
				swap(&arr[i], &arr[i + 1]);
				flag = true;
			}
		}
		if (flag == false)
			break;
	}
}

//ѡ������
/*
* ѡ������Ĺ����ǣ�
	1.�ҵ������е���СԪ�أ�Ȼ�����������ĵ�һ��λ���ϵ�Ԫ�ؽ�������������Լ���С�ͺ��Լ�������
	2.Ȼ���ٴ�ʣ�µ��������ҵ���С��Ԫ�أ�������ĵڶ���λ���ϵ�Ԫ�ؽ�����
	3.����������Ԫ�ض���ѡȡ��һ���㷨����;
* ѡ������Ĳ���������ȷ���ģ�N(N-1)/2�αȽϣ�N�ν���������ζ�������ص㣺
	1.����ʱ��������������ȫû�й�ϵ���������ٵĲ���Ѿ���������в�������ٲ���ʱ��
	2.���ݵ��ƶ������ٵģ�ֻ����N�ν�����
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

//��������
/*
* ��������Ĺ����ǣ�
	*�����Ƶ�ʱ�����ǰѺ��������Ʋ��뵽һ�����ʵ�λ�á�
	1.��ǰ������ߵĲ��������򲿷֣������ǵ�����λ�û���ȷ����Ϊ�˸������Ԫ������λ�ã�������Ҫ�ƶ����ǵ�λ�á�
	2.�������������Ҷ˵�ʱ�����������ˡ�
* ���������������������ʱ���ܶ࣬�����������кܴ�Ĺ�ϵ��
* ������������õ��������ҪN-1�αȽϣ�0�ν���������ҪN^2/2�αȽϺ�N^2/2�ν�����ƽ����N^2/4�αȽϺͽ���
* ���������ѡ������Ҫ��һ��㡣
*/

void insertion_sort(elemtype arr[], int n)//����д���ٶ����
{
	for (int pos = 1; pos < n; pos++) {
		if (arr[pos - 1] > arr[pos]) {//����Ҫ��Ҫ�ƶ�Ԫ��
			elemtype temp = arr[pos];
			int i;
			for (i = pos; arr[i - 1] > temp; i--) //�ƶ��ڳ�λ��
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
		for (i = pos; i > 0 && arr[i - 1] > temp; i--) //��arr[pos],���뵽arr[pos-1]~arr[0]֮��
			arr[i] = arr[i - 1];
		arr[i] = temp;
	}
}

void insertion_sort2(elemtype arr[], int n)//����д�����ƶ�Ԫ�أ����ѵ�ʱ���ѡ������Ҫ��һ��,���Ǻܺü�
{
	for (int pos = 1; pos < n; pos++) {
		for (int i = pos; i > 0 && arr[i - 1] > arr[i]; i--) {
			swap(&arr[i - 1], &arr[i]);
		}
	}
}

//�۰��������
/*
* ���������һ���ص��ǣ��������������������У��Ҳ��ǲ��ᱻ���ʵġ�
  ������Ѱ�Ҳ����λ�õ�ʱ�򣬿��Բ������Ƚϣ�����ʹ�ö��ֲ������Ľ���
*/

void insertion_sort_log2(elemtype arr[], int n)//�ٶ��������Ǻܿ�
{
	for (int pos = 1; pos < n; pos++) {
		elemtype temp = arr[pos];//���ݴ�Ԫ��

		int left = 0;
		int right = pos - 1;
		while (left <= right) {
			int middle = left + (right - left) / 2;
			if (arr[middle] > arr[pos])
				right = middle - 1;
			else
				left = middle + 1;
		}

		for (int i = pos; i > right + 1; i--) {//right+1=middle�ƶ�Ԫ��
			arr[i] = arr[i - 1];
		}
		arr[right + 1] = temp;
	}
}

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

//������
/*
* ����������ѡ�������ϵĸĽ���
* ���ǰ������������н��ѣ�Ȼ����ɾ����С�ѣ��ռ�ɾ����Ԫ�صõ�����Ľ����
* �����뷨�������ǣ�������Ҫһ��������������ռ�ɾ����Ԫ���ٸ��ƻ�ԭ���顣
* �Ľ��ķ�����ʹ�����ѣ�ɾ�������Ժ��ɾ����Ԫ�طŵ���������һλ��ֻ��Ҫһ����ʱ�����ݴ�һ��ɾ���ĶѶ�Ԫ��
*
* ������ҪO(N),N��ɾ������O(NlogN).
*
*/

void sink(int arr[], int n, int k)
{
	while (2 * k + 1 <= n) {
		int i = 2 * k + 1;
		if (i < n && (arr[i] < arr[i + 1]))
			i++;//iָ��ϴ���Ǹ��ӽ��

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

//��������
//K&R�е�д����ʹ�ÿ���ָ��
void q_sort(int arr[], int left, int right)
{
	if (left >= right)//�ݹ��ֹ����
		return;

	int i;
	int last;
	int pivot = left + (right - left) / 2;

	swap(&arr[pivot], &arr[left]);//������ߵ�Ԫ����Ϊ�зֵ�
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (arr[i] < arr[left]) {//last����ָ�룬i�ǿ�ָ��
			last++;//���i����Ԫ�ش����з�Ԫ�أ�i�Ϳ���ͻ��
			swap(&arr[i], &arr[last]);//���i����Ԫ��С���з�Ԫ�أ���ô�Ϳ���֪ͨlast�ƶ��ڳ�һ������λ��
		}
	}

	//�Ŷ��з�Ԫ��
	swap(&arr[left], &arr[last]);//last������з�Ԫ�ص�����λ�ã������Ԫ�ض�С���з�Ԫ��
	q_sort(arr, left, last - 1);
	q_sort(arr, last + 1, right);
}

void quick_sort(int arr[], int n)
{
	q_sort(arr, 0, n - 1);
}

//���������������pivot��ѡȡ�й�
//ѡȡ�����м䡢��������Ԫ�ص���λ����Ϊpivot
int median3(int arr[], int left, int right)
{
	//����ʹ: arr[left] < arr[center] < arr[right]
	int center = left + (right - left) / 2;
	if (arr[left] > arr[center])
		swap(&arr[left], &arr[center]);
	if (arr[left] > arr[right])
		swap(&arr[left], &arr[right]);
	if (arr[center] > arr[right])
		swap(&arr[center], &arr[right]);

	swap(&arr[right - 1], &arr[center]);//��pivot�ŵ������ڶ���λ��
	int pivot = arr[center];
	return pivot;
}

//�������ģ��Сʱ����Ϊ�������򣬳�Խд��
void q_sort1(int arr[], int left, int right)
{
	int pivot;
	int cutoff = 50;
	int lo, hi;

	if (cutoff <= (right - left + 1)) {
		pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
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

		//�Ŷ�pivot��λ��
		swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
		q_sort1(arr, left, lo - 1);
		q_sort1(arr, lo + 1, right);
	}
	else
		insertion_sort(arr + left, right - left + 1);//����arr + left�ǵݹ����Ҫ
}

//sedgewickд����ֻ���п�������
void q_sort2(int arr[], int left, int right)
{
	if (left >= right)//�ݹ��ֹ����
		return;

	int pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
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

	//�Ŷ�pivot��λ��
	swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
	q_sort2(arr, left, lo - 1);
	q_sort2(arr, lo + 1, right);
}

void q_sort3(int arr[], int left, int right)
{
	int cutoff = 100;
	if (left + cutoff >= right) {//�������ģ��Сʱ��Ϊ��������
		insertion_sort(arr + left, right - left + 1);
		return;//�ݹ��ֹ����
	}
		
	int pivot = median3(arr, left, right);//��һ��������pivot�ŵ��˵����ڶ���λ�ã����ҵ�����һ��λ���ϵ�Ԫ��Ҳ����pivot
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

	//�Ŷ�pivot��λ��
	swap(&arr[lo], &arr[right - 1]);//pivot����arr[right-1],loʱpivot������λ��
	q_sort3(arr, left, lo - 1);
	q_sort3(arr, lo + 1, right);
}

//�����зֿ������򣬴����ظ�Ԫ�ؽ϶�������
/*
* �������ظ�Ԫ�ؽ϶�ʱ������������ϣ���Ľ�������
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

//Ͱ����ͻ�������
/*
* Ͱ����Ҫ����֪������Ԫ�ص�ȡֵ��Χ������ȡֵ��Χ��0~M-1,��ô����ҪM��Ͱ��
* Ͱ��ʵ��������Ľ�㣬���ڷ�����ռ�������������
* ���������Ƕ�ؼ�ֵ��Ͱ���򣬱���һ����λ��������λ��ʮλ����λ����������������Ҫ��������Ͱ����
  ������������ظ�����Ͱ�����Կռ���ۻ���O(M).
* һ��أ������d���ؼ��֣���ô��Ҫ����d��Ͱ���򣬷�Ϊ��λ����MSD����λ����LSD��
* �������˿��������ӣ���λ�ǻ�ɫ����λ����ֵ����ôLSDЧ�ʱ�MSDҪ��һ�㣬��ΪLSD���ڷ����ռ����ԣ�MSD���ڷ��β��ԣ��ֱ������ٺϲ����
* �����N���ؼ��֣���ôһ���������ҪN�������M���ռ����ܵ�ʱ����۾���O(d*(N+M));
* �����ֽ����⣺
  ������ǰ�ȡֵ��Χ������Ͱ����ô���ܴ����޴�Ŀռ��˷ѣ������20����������λ��������������������Ҫ1000��Ͱ
  ���������10Ϊ��������λ�����ֽ⣬��ôȡֵ��Χ�����0~9��ֻ��Ҫ����10��Ͱ����Ӧ��������Ҫ��������
  һ��أ���RΪ�����ֽ⣬��ֻ��ҪR��Ͱ��
* 
*/

//ʵ����λ�����Ļ�������
#define MAX_digit 4//ÿ��Ԫ�����Ĺؼ�����
#define Radix 10

//����һ��bucket
typedef struct Node* ptr_to_Node;
struct Node {
	int key;
	ptr_to_Node next;
};

//bucketͷ���
struct head_node {
	ptr_to_Node head;
	ptr_to_Node tail;
};

typedef struct head_node bucket[Radix];

//Լ����λD=1����λD<=MAX_digit
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

	for (i = 0; i < Radix; i++)//��ʼ��ÿ��ͰΪ������
		B[i].head = B[i].tail = NULL;

	for (i = 0; i < n; i++) {//��arr[]�������List
		temp = (ptr_to_Node)malloc(sizeof(struct Node));
		temp->key = arr[i];
		temp->next = List;
		List = temp;
	}

	//�����￪ʼ����
	for (D = 1; D <= MAX_digit; D++) {
		//�������
		p = List;
		while (p) {
			Di = get_digit(p->key, D);
			temp = p;//��List��ժ��
			p = p->next;
			temp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = temp;
			else {
				B[Di].tail->next = temp;
				B[Di].tail = temp;
			}
		}

		//�ռ�����
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--) {
			if (B[Di].head) {
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL;//���Ͱ
			}
		}
	}

	for (i = 0; i < n; i++) {//��List�Ż�arr[]���ͷſռ�
		temp = List;
		List = List->next;
		arr[i] = temp->key;
		free(temp);
	}
}

//�ⲿ����
/*
* ���ڴ��Ϊ�����֣��������뻺���һ���������
* ���������·�鲢
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