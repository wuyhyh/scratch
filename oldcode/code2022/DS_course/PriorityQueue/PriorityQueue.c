#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef int elemtype;

typedef struct Hnode* ptr_to_Hnode;
struct Hnode {
	elemtype* data;
	int size;
	int capacity;
};
typedef ptr_to_Hnode Heap;
//最大堆

#define MAXDATA 1e5
Heap create_Heap(int maxsize)//主要是开辟内存空间
{
	Heap H = (Heap)malloc(sizeof(struct Hnode));
	H->data = (elemtype*)malloc((maxsize + 1) * sizeof(elemtype));
	H->size = 0;
	H->capacity = maxsize;
	H->data[0] = MAXDATA;//存放一个大于堆中所有元素的数据
	return H;
}

bool is_full_Heap(Heap H)
{
	return (H->size == H->capacity);
}

bool is_empty_Heap(Heap H)
{
	return (H->size == 0);
}

bool insert_Heap(Heap H, elemtype e)
{
	if (is_full_Heap(H)) {
		printf("Heap is full\n");
		return false;
	}

	int i = ++H->size;//堆的最后一个位置,新人加入团伙
	for (; e > H->data[i / 2]; i /= 2) {
		H->data[i] = H->data[i / 2];
	}
	H->data[i] = e;
	return true;
}

elemtype delete_Heap(Heap H)
{
	if (is_empty_Heap(H)) {
		printf("Heap is empty\n");
		return -1;
	}

	int parent, child;
	elemtype max_vlaue, last_one;

	max_vlaue = H->data[1];
	last_one = H->data[H->size--];
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		if ((child != H->size) && (H->data[child] < H->data[child + 1]))//这里要仔细理解
			child++;//child指向大的那个结点
		if (last_one > H->data[child])
			break;//旧王已死，新王当立
		else
			H->data[parent] = H->data[child];//压不住手下
	}
	H->data[parent] = last_one;
	return max_vlaue;
}

void percolator_down(Heap H, int pos)//把以pos为根结点的堆调整为最大堆
{
	int parent, child;
	elemtype e;

	e = H->data[pos];
	for (parent = pos; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		if ((child != H->size) && (H->data[child] < H->data[child + 1]))
			child++;
		if (e > H->data[child])
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent] = e;
}

void build_Heap(Heap H)
{
	for (int i = H->size / 2; i > 0; i--) {
		percolator_down(H, i);
	}
}

Heap construct_Heap(int arr[], int n)
{
	Heap H = create_Heap(n);
	for (int i = 0; i < n; i++) {
		H->data[i + 1] = arr[i];
	}
	H->size = n;
	for (int i = H->size / 2; i > 0; i--) {
		percolator_down(H, i);
	}
	return H;
}

int main()
{
	Heap h = create_Heap(20);
	int arr[] = { 79,66,87,91,72,43,38,55,83,30,49,9 };
	for (int i = 0; i < 12; i++){
		insert_Heap(h, arr[i]);
	}

	for (int i = 1; i <= h->size; i++) {
		printf("arr[%d] ", i);
	}
	putchar('\n');
	for (int i = 1; i <= h->size; i++) {
		printf("%6d ", arr[i-1]);
	}
	putchar('\n');
	for (int i = 1; i <= h->size; i++) {
		printf("%6d ", h->data[i]);
	}
	putchar('\n');

	for (int i = 0; i < 12; i++) {
		printf("%6d ", delete_Heap(h));
	}
	printf("\n*************************************************\n");

	int arr2[] = { 79,66,87,91,72,43,38,55,83,30,49,9 };
	for (int i = 1; i <= 12; i++) {
		printf("arr[%d] ", i);
	}
	putchar('\n');
	for (int i = 1; i <= 12; i++) {
		printf("%6d ", arr2[i-1]);
	}

	Heap h2 = create_Heap(20);
	for (int i = 1; i <= 12; i++) {
		h2->data[i] = arr2[i-1];
	}
	h2->size = 12;

	build_Heap(h2);

	putchar('\n');
	for (int i = 1; i <= 12; i++) {
		printf("%6d ", h2->data[i]);
	}
	putchar('\n');

	for (int i = 0; i < 12; i++) {
		printf("%6d ", delete_Heap(h2));
	}

	printf("\n*************************************************\n");
	Heap h3 = construct_Heap(arr2, 12);
	for (int i = 1; i <= 12; i++) {
		printf("%6d ", h3->data[i]);
	}

	putchar('\n');
	for (int i = 0; i < 12; i++) {
		printf("%6d ", delete_Heap(h3));
	}

	return 0;
}