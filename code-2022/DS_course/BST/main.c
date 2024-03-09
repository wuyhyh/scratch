#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct BSTnode* ptr_to_BSTnode;
struct BSTnode {
	int data;
	ptr_to_BSTnode left;
	ptr_to_BSTnode right;
};
typedef ptr_to_BSTnode Bintree;

void inorder(Bintree BST)
{
	if (BST) {
		inorder(BST->left);
		printf("%d ", BST->data);
		inorder(BST->right);
	}
}

int get_height(Bintree BST)
{
	int height_L;
	int height_R;
	int max_height = 0;

	if (BST) {
		height_L = get_height(BST->left);
		height_R = get_height(BST->right);
		max_height = (height_L > height_R) ? height_L : height_R;
		return max_height + 1;
	}
	else {
		return 0;//空树高度为0
	}
}

Bintree recursive_find_BST(Bintree BST, int e)
{
	if (!BST)//先检测退出条件
		return NULL;//not find

	if (e < BST->data)
		return recursive_find_BST(BST->left, e);
	else if (e > BST->data)
		return recursive_find_BST(BST->right, e);
	else
		return BST;//BST就是要找的e
}

Bintree find_BST(Bintree BST, int e)//尾递归可以修改为迭代
{
	while (BST) {
			if (e > BST->data)
				BST = BST->right;
			else if (e < BST->data)
				BST = BST->left;
			else
				break;
	}
	return BST;//返回NULL或者找到的地址
}

Bintree recursive_find_min(Bintree BST)
{
	if (!BST)
		return NULL;//空树返回
	else if (!BST->left)//已经到达最左端点
		return BST;
	else
		recursive_find_min(BST->left);//继续在左子树里面找
}

Bintree recursive_find_max(Bintree BST)
{
	if (!BST)
		return NULL;
	else if (!BST->right)
		return BST;
	else
		recursive_find_max(BST->right);
}

Bintree find_min(Bintree BST)
{
	if (BST){//如果不是空树就不断向左
		while (BST->left) 
			BST = BST->left;
	}
	return BST;
}

Bintree find_max(Bintree BST)
{
	if (BST) {
		while (BST->right) 
			BST = BST->right;
	}
	return BST;
}

Bintree recursive_insert_BST(Bintree BST,int e)
{
	if (!BST) {
		BST = (Bintree)malloc(sizeof(struct BSTnode));
		BST->data = e;
		BST->left = BST->right = NULL;
	}
	else {
		if (e < BST->data)
			BST->left = recursive_insert_BST(BST->left, e);//递归调用的时候记住返回值不要忽略
		else if (e > BST->data)
			BST->right = recursive_insert_BST(BST->right, e);
		//BST已经存在，什么都不做
	}
	return BST;
}

Bintree insert_BST(Bintree BST, int e)
{
	//不知道有没有实现的必要？20220623
}

Bintree recursive_delete_BST(Bintree BST, int e)
{
	if (!BST)
		printf("no such element\n");
	else {
		if (e < BST->data) {
			BST->left = recursive_delete_BST(BST->left, e);
		}
		else if (e > BST->data) {
			BST->right = recursive_delete_BST(BST->right, e);
		}
		else {//BST就是要删除的结点，有三种可能，并且我们选用右子树的最小值来继承遗产，推恩令要求
			if (BST->left && BST->right) {
				Bintree temp = find_min(BST->right);//选用右子树的最小值来继承遗产
				BST->data = temp->data;
				BST->right = recursive_delete_BST(BST->right, temp->data);
			}
			else {//只有一个孩子或者没有孩子
				Bintree temp = BST;
				if (!BST->left) //只有右孩子或者没有孩子
					BST = BST->right;
				else 
					BST = BST->left;
				free(temp);
			}
		}
	}

	return BST;
}

int main()
{
	Bintree A = (Bintree)malloc(sizeof(struct BSTnode)); A->data = 30;
	Bintree B = (Bintree)malloc(sizeof(struct BSTnode)); B->data = 15;
	Bintree C = (Bintree)malloc(sizeof(struct BSTnode)); C->data = 41;
	Bintree D = (Bintree)malloc(sizeof(struct BSTnode)); D->data = 33;
	Bintree E = (Bintree)malloc(sizeof(struct BSTnode)); E->data = 50;

	A->left = B; A->right = C;
	B->left = B->right = NULL;
	C->left = D; C->right = E;
	D->left = D->right = NULL;
	E->left = E->right = NULL;

	Bintree tree = A;
	printf("inorder traversal BST: \n");
	inorder(tree);

	tree = recursive_insert_BST(tree, 100);
	printf("\ninorder traversal BST: \n");
	inorder(tree);

	tree = recursive_delete_BST(tree, 41);
	printf("\ninorder traversal BST: \n");
	inorder(tree);

	printf("\nheight of BST = %d\n", get_height(tree));

	Bintree t = recursive_find_BST(tree, 33);
	if(t)
		printf("\n%d \n", t->data);

	Bintree t1 = find_BST(tree, 41);
	if(t1)
		printf("\n%d \n", t1->data);

	Bintree t2 = recursive_find_min(tree);
	if (t2)
		printf("\nmin = %d \n", t2->data);

	Bintree t3 = recursive_find_max(tree);
	if (t3)
		printf("\nmax = %d \n", t3->data);

	Bintree t4 = find_min(tree);
	if (t4)
		printf("\nmin = %d \n", t4->data);

	Bintree t5 = find_max(tree);
	if (t5)
		printf("\nmax = %d \n", t5->data);

	return 0;
}

//20220623