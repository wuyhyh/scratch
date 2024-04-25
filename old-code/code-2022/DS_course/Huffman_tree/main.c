#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"Huffman.h"
#include"minHeaph.h"

Huffman_tree Huffman(int arr[],int n)
{
	Huffman_tree H_arr[20];
	for (int i = 0; i < n; i++) {
		H_arr[i] = (Huffman_tree*)malloc(sizeof(struct HTnode));
		H_arr[i]->weight = arr[i];
		H_arr[i]->left = H_arr[i]->right = NULL;
	}

	Heap H = build_Heap(H_arr, n);
	Huffman_tree T;
	for (int i = 1; i <= n - 1; i++) {
		T = (Huffman_tree*)malloc(sizeof(struct HTnode));
		T->left = delete_Heap(H);
		T->right = delete_Heap(H);
		T->weight = T->left->weight + T->right->weight;
		insert_Heap(H, T);
	}

	return delete_Heap(H);
}

void inorder(Huffman_tree T)
{
	if (T) {
		inorder(T->left);
		printf("%d ", T->weight);
		inorder(T->right);
	}
}

int main()
{
	int arr[] = { 1,2,3,4,5 };
	Huffman_tree tree = Huffman(arr, 5);
	inorder(tree);

	return 0;
}