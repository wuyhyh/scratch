#pragma once
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct HTnode* ptr_to_HTnode;
struct HTnode {
	int weight;
	ptr_to_HTnode left;
	ptr_to_HTnode right;
};
typedef ptr_to_HTnode Huffman_tree;


typedef ptr_to_HTnode elemtype;

typedef struct Hnode* ptr_to_Hnode;
struct Hnode {
	elemtype* data;
	int size;
	int capacity;
};
typedef ptr_to_Hnode Heap;//最小堆

Heap create_Heap(int maxsize)
{
	Heap H = (Heap)malloc(sizeof(struct Hnode));
	H->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	H->size = 0;
	H->capacity = maxsize;
	return H;
}

void percolator_down(Heap H,int pos)
{
	int parent, child;
	elemtype e;

	e = H->data[pos];
	for (parent = pos; parent * 2 <= H->size;parent=child) {
		child = parent * 2;
		if (child != H->size && (H->data[child]->weight > H->data[child + 1]->weight))//取子结点中较小者
			child++;
		if (e->weight <= H->data[child]->weight)
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent] = e;
}

Heap build_Heap(elemtype arr[], int n)
{
	Heap H = create_Heap(n);
	H->size = n;
	for (int i = 0; i < H->size; i++)
		H->data[i + 1] = arr[i];
	for (int i = H->size / 2; i > 0; i--)
		percolator_down(H, i);
	return H;
}

bool is_empty_Heap(Heap H)
{
	return H->size == 0;
}

bool is_full_Heap(Heap H)
{
	return H->size == H->capacity;
}

bool insert_Heap(Heap H, elemtype e)
{
	if (is_full_Heap(H)) {
		printf("Heap is full\n");
		return false;
	}

	int i = ++H->size;
	for (; (H->data[i / 2])->weight < e->weight; i /= 2) {
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

	elemtype min_value = H->data[1];
	elemtype e = H->data[H->size--];
	H->data[1] = e;
	percolator_down(H, 1);
	return min_value;
}
