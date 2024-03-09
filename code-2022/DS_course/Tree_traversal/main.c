#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"Stack.h"
#include"Queue.h"
#include"tree.h"

void recursive_inorder(Bintree BT)
{
	if (BT) {
		recursive_inorder(BT->left);
		printf("%c ", BT->data);
		recursive_inorder(BT->right);
	}
}

void recursive_preorder(Bintree BT)
{
	if (BT) {
		printf("%c ", BT->data);
		recursive_preorder(BT->left);
		recursive_preorder(BT->right);
	}
}

void recursive_postorder(Bintree BT)
{
	if (BT) {
		recursive_postorder(BT->left);
		recursive_postorder(BT->right);
		printf("%c ", BT->data);
	}
}

void inorder(Bintree BT)
{
	if (!BT)
		return;

	Stack S = create_Stack(20);
	Bintree T = BT;

	while (T || !is_empty_Stack(S)) {
		while (T) {
			push(S, T);
			T = T->left;
		}
		T = pop(S);
		printf("%c ", T->data);
		T = T->right;
	}
}

void preorder(Bintree BT)
{
	if (!BT)
		return;

	Stack S = create_Stack(20);
	Bintree T = BT;

	push(S, T);
	while (!is_empty_Stack(S)) {
		T = pop(S);
		printf("%c ", T->data);
		if (T->right)
			push(S, T->right);
		if (T->left)
			push(S, T->left);
	}
}

void postorder(Bintree BT)
{
	if (!BT)
		return;

	Stack stackA = create_Stack(20);
	Stack StackB = create_Stack(20);
	Bintree T = BT;

	push(stackA, T);
	while (!is_empty_Stack(stackA)) {
		T = pop(stackA);
		push(StackB,T);
		if (T->left)
			push(stackA, T->left);
		if (T->right)
			push(stackA, T->right);
	}

	while (!is_empty_Stack(StackB)) {
		T = pop(StackB);
		printf("%c ", T->data);
	}
}

void levelorder(Bintree BT)
{
	if (!BT)
		return;

	Queue Q = create_Queue(20);
	Bintree T = BT;

	add_Queue(Q, T);
	while (!is_empty_Queue(Q)) {
		T = delete_Queue(Q);
		printf("%c ", T->data);
		if (T->left)
			add_Queue(Q,T->left);
		if (T->right)
			add_Queue(Q,T->right);
	}
}

//输出叶节点
void preorder_print_leaves(Bintree BT)
{
	if (BT) {
		if ((!BT->left) && (!BT->right)) {
			printf("%c ", BT->data);
		}
		preorder_print_leaves(BT->left);
		preorder_print_leaves(BT->right);
	}
}

int tree_height(Bintree BT)
{
	int height_L = 0;
	int height_R = 0;
	int maxH = 0;

	if (BT) {
		height_L = tree_height(BT->left);
		height_R = tree_height(BT->right);
		maxH = (height_L > height_R) ? height_L : height_R;
		return maxH + 1;
	}
	else {
		return 0;//空树的高度是0
	}
}

int main()
{
	Bintree A = (Bintree)malloc(sizeof(struct Tnode));A->data = 'A';
	Bintree B = (Bintree)malloc(sizeof(struct Tnode));B->data = 'B';
	Bintree C = (Bintree)malloc(sizeof(struct Tnode));C->data = 'C';
	Bintree D = (Bintree)malloc(sizeof(struct Tnode));D->data = 'D';
	Bintree E = (Bintree)malloc(sizeof(struct Tnode));E->data = 'E';
	Bintree F = (Bintree)malloc(sizeof(struct Tnode));F->data = 'F';
	Bintree G = (Bintree)malloc(sizeof(struct Tnode));G->data = 'G';
	Bintree H = (Bintree)malloc(sizeof(struct Tnode));H->data = 'H';
	Bintree I = (Bintree)malloc(sizeof(struct Tnode));I->data = 'I';

	A->left = B;A->right = C;
	B->left = D;B->right = F;
	C->left = G;C->right = I;
	D->left = NULL;D->right = NULL;
	E->left = NULL;E->right = NULL;
	F->left = E;F->right = NULL;
	G->left = NULL;G->right = H;
	H->left = NULL;H->right = NULL;
	I->left = NULL;I->right = NULL;

	Bintree tree = A;
	printf("constructed\n");

	printf("\nrecursive inorder:\n");
	recursive_inorder(tree);

	printf("\nrecursive preorder:\n");
	recursive_preorder(tree);

	printf("\nrecursive postorder:\n");
	recursive_postorder(tree);

	printf("\ninorder:\n");
	inorder(tree);

	printf("\npreorder:\n");
	preorder(tree);

	printf("\npostorder:\n");
	postorder(tree);

	printf("\nlevelorder:\n");
	levelorder(tree);

	printf("\nleaves of tree:\n");
	preorder_print_leaves(tree);

	printf("\nheght of tree = %d\n",tree_height(tree));

	return 0;
}

//A B D F E C G H I
//A B D F E C G H I
//D B E F A G H C I
//D B E F A G H C I
//D E F B H G I C A
//D E F B H G I C A  A B C D F G I E H