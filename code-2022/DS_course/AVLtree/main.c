#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef char* elemtype;

typedef struct AVLnode* ptr_to_AVLnode;
struct AVLnode {
	elemtype data;
	ptr_to_AVLnode left;
	ptr_to_AVLnode right;
	int height;
};
typedef ptr_to_AVLnode AVLtree;

void inorder(AVLtree T)
{
	if (T) {
		inorder(T->left);
		printf("%s ", T->data);
		inorder(T->right);
	}
}

int max_one(int a, int b)
{
	return (a > b) ? a : b;
}

int get_height(AVLtree T)
{
	int hl;
	int hr;
	int maxh = 0;

	if (T) {
		hl = get_height(T->left);
		hr = get_height(T->right);
		maxh = max_one(hl, hr);
		return maxh + 1;
	}
	else
		return 0;
}

AVLtree single_left_rotation(AVLtree A)
{
	AVLtree B = A->left;
	A->left = B->right;
	B->right = A;
	A->height = max_one(get_height(A->left), get_height(A->right)) + 1;
	B->height = max_one(get_height(B->left), get_height(B->right)) + 1;
	return B;
}

AVLtree single_right_rotation(AVLtree A)
{
	AVLtree B = A->right;
	A->right = B->left;
	B->left = A;
	A->height = max_one(get_height(A->left), get_height(A->right)) + 1;
	B->height = max_one(get_height(B->left), get_height(B->right)) + 1;
	return B;
}

AVLtree double_left_right_rotation(AVLtree A)
{
	A->left = single_right_rotation(A->left);
	return single_left_rotation(A);
}

AVLtree double_right_left_rotation(AVLtree A)
{
	A->right = single_left_rotation(A->right);
	return single_right_rotation(A);
}

AVLtree insert_AVLtree(AVLtree T, elemtype e)
{
	if (!T) {
		T = (AVLtree)malloc(sizeof(struct AVLnode));
		T->data = e;
		T->left = T->right = NULL;
		T->height = 1;
		return T;
	}
	else {
		if (e < T->data) {
			T->left = insert_AVLtree(T->left, e);
			if ((get_height(T->left) - get_height(T->right)) == 2) {//如果需要左旋
				if (e < T->left->data)
					T = single_left_rotation(T);
				else
					T = double_left_right_rotation(T);
			}
		}//左子树插入结束
		else if (e > T->data) {
			T->right = insert_AVLtree(T->right, e);
			if ((get_height(T->left) - get_height(T->right)) == -2) {//如果需要右旋
				if (e > T->right->data)
					T = single_right_rotation(T);
				else
					T = double_right_left_rotation(T);
			}
		}//右子树插入结束

		T->height = max_one(get_height(T->left), get_height(T->right));
		return T;
	}
}

int main()
{
	AVLtree tree = NULL;
	char* month[12] = { "January","Febuary","March","April","May","June","July","August","September","Octber","November","December" };
	for (int i = 0; i < 12; i++) {
		tree = insert_AVLtree(tree, month[i]);
	}
	printf("height = %d\n", get_height(tree));
	inorder(tree);

	return 0;
}