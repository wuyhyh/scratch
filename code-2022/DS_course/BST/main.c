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
		return 0;//�����߶�Ϊ0
	}
}

Bintree recursive_find_BST(Bintree BST, int e)
{
	if (!BST)//�ȼ���˳�����
		return NULL;//not find

	if (e < BST->data)
		return recursive_find_BST(BST->left, e);
	else if (e > BST->data)
		return recursive_find_BST(BST->right, e);
	else
		return BST;//BST����Ҫ�ҵ�e
}

Bintree find_BST(Bintree BST, int e)//β�ݹ�����޸�Ϊ����
{
	while (BST) {
			if (e > BST->data)
				BST = BST->right;
			else if (e < BST->data)
				BST = BST->left;
			else
				break;
	}
	return BST;//����NULL�����ҵ��ĵ�ַ
}

Bintree recursive_find_min(Bintree BST)
{
	if (!BST)
		return NULL;//��������
	else if (!BST->left)//�Ѿ���������˵�
		return BST;
	else
		recursive_find_min(BST->left);//������������������
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
	if (BST){//������ǿ����Ͳ�������
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
			BST->left = recursive_insert_BST(BST->left, e);//�ݹ���õ�ʱ���ס����ֵ��Ҫ����
		else if (e > BST->data)
			BST->right = recursive_insert_BST(BST->right, e);
		//BST�Ѿ����ڣ�ʲô������
	}
	return BST;
}

Bintree insert_BST(Bintree BST, int e)
{
	//��֪����û��ʵ�ֵı�Ҫ��20220623
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
		else {//BST����Ҫɾ���Ľ�㣬�����ֿ��ܣ���������ѡ������������Сֵ���̳��Ų����ƶ���Ҫ��
			if (BST->left && BST->right) {
				Bintree temp = find_min(BST->right);//ѡ������������Сֵ���̳��Ų�
				BST->data = temp->data;
				BST->right = recursive_delete_BST(BST->right, temp->data);
			}
			else {//ֻ��һ�����ӻ���û�к���
				Bintree temp = BST;
				if (!BST->left) //ֻ���Һ��ӻ���û�к���
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