//����������ʽ�洢

//������ADT
/*
	���ݼ�������Ľ��ļ��ϡ�������Ͽ���Ϊ�գ��ǿյĻ�����һ�����ڵ�����������������ɡ�
	��������
	1.create
	2.is_empty
	3.traversal//����
*/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int elemtype;

typedef struct BTnode* p_to_BTnode;
typedef p_to_BTnode Bintree;
struct BTnode {
	elemtype data;//�������ָ�����Һ��ӵ�ָ��
	Bintree left;
	Bintree right;
};

//����:�����
void inorder_traversal(Bintree BT)
{
	if (BT) {
		inorder_traversal(BT->left);
		printf("%d ", BT->data);
		inorder_traversal(BT->right);
	}
}

//���򣺸�����
void preorder_traversal(Bintree BT)
{
	if (BT) {
		printf("%d ", BT->data);
		preorder_traversal(BT->left);
		preorder_traversal(BT->right);
	}
}

//�������Ҹ�
void postorder_traversal(Bintree BT)
{
	if (BT) {
		postorder_traversal(BT->left);
		postorder_traversal(BT->right);
		printf("%d ", BT->data);
	}
}

//�ǵݹ����
/*
	�ݹ�����Ĵ���ܼ�൫��Ч�ʲ��ߣ��ݹ鱾��������ջʵ�ֵģ����ǲ����м���׬��ۣ�ֱ�ӽ�����ջʵ�ַǵݹ����
	�������򡢺������ʱ��������˳����һ���ģ�ֻ�Ƿ��ʵ�ʱ����һ��
	���������ķǵݹ�Ҫ��һ�㣬���������Ҫ���ν�һ��Ԫ����ջ��Ҫ����һ��
*/

#define MAXSIZE 100

typedef struct Snode* p_to_Snode;
struct Snode {
	Bintree data[MAXSIZE];
	int top;
};
typedef p_to_Snode Stack;

Stack create_S()
{
	Stack S = (Stack)malloc(sizeof(struct Snode));
	S->top = -1;
	return S;
}

bool is_empty_S(Stack S)
{
	return S->top == -1;
}

void push(Stack S, Bintree BT)
{
	S->data[S->top++] = BT;
}

Bintree pop(Stack S)
{
	return S->data[--S->top];
}

//��������ķǵݹ�ʵ��
//�����
/*
	1.����һ��������ѹ��ջ��ȥ����������������ֱ��������������
	2.������������󣬴�ջ���浯������������
	3.��ȥ����������
*/

void inorder_tra(Bintree BT)
{
	Stack S = create_S();
	Bintree T = BT;

	while (T || !is_empty_S(S)) {//����ջ���Ƿǿյ�
		while (T) {//һ·����
			push(S, T);
			T = T->left;
		}
		T = pop(S);//����������
		printf("%d ", T->data);
		T = T->right;//ת��������
	}
}

void preorder_tra(Bintree BT);

void postorder_tra(Bintree BT);

/*
	�����������ĺ��������ǰ�һ����ά�ṹ���Ի�Ϊһ������
	�ؼ��ǽ���һ���洢�ṹ�������ݲ����ʵĽ��
	��Stack����ʵ���������򡢺�����ʣ���Queueʵ�ֲ������
*/

typedef struct Qnode* p_to_Qnode;
struct Qnode {
	Bintree* data;
	int front;
	int rear;
	int maxsize;
};
typedef p_to_Qnode Queue;

Queue create_Q(int maxsize)
{
	Queue Q = (Queue)malloc(sizeof(struct Qnode));
	Q->data = (Bintree*)malloc(maxsize * sizeof(Bintree));
	Q->front = 0;
	Q->rear = 0;
	Q->maxsize = maxsize;
	return Q;
}

bool is_full_Q(Queue Q)
{
	return (Q->front + 1) % Q->maxsize == (Q->rear);
}

bool is_empty_Q(Queue Q)
{
	return Q->front == Q->rear;
}

bool add_Q(Queue Q, Bintree BT)
{
	if (is_full_Q(Q)) {
		printf("full\n");
		return false;
	}
	else {
		Q->rear = (Q->rear + 1) % Q->maxsize;//Q->rear+1 < Q->maxsize
		Q->data[Q->rear] = BT;
		return true;
	}
}

Bintree delete_Q(Queue Q)
{
	if (is_full_Q(Q)) {
		printf("empty\n");
		return false;
	}
	else {
		Q->front = (Q->front + 1) % Q->maxsize;//Q->front�������ƶ�
		return Q->data[Q->front];
	}
}

//���������һ��һ��ط���
/*
	����������ʵ�֣�
	1.�Ӷ�����ȡ��һ��Ԫ��
	2.������
	3.������Ԫ�������Һ��ӣ������ĺ��ӷ������
*/

void level_order_traversal(Bintree BT)
{
	if (!BT)
		return;//����ֱ�ӷ���

	Bintree T;
	Queue Q = create_Q(100);
	add_Q(Q, BT);
	while (!is_empty_Q(Q)) {
		T = delete_Q(Q);
		printf("%d ", T->data);
		if (T->left)
			add_Q(Q, T->left);
		if (T->right)
			add_Q(Q, T->right);
	}
}

//�������Ҷ�ڵ�
void preorder_print_leaves(Bintree BT)
{
	if (BT) {
		if ((!BT->left) && (!BT->right)) {//�����Ҷ�ڵ�
			printf("%d ", BT->data);
		}
		preorder_print_leaves(BT->left);
		preorder_print_leaves(BT->right);
	}
}

//��������ĸ߶�
//Height = max{H_left,H_right}+1;//Ҳ�ǵݹ飬ʹ�ú����������ΪҪ��֪�����������ĸ߶�
int get_height(Bintree BT)
{
	int Hl, Hr, maxH;

	if (BT) {
		Hl = get_height(BT->left);
		Hr = get_height(BT->right);
		maxH = (Hl > Hr) ? Hl : Hr;
		return maxH + 1;//����β�ݹ�
	}
	return 0;
}

//������������
//�������Ƿ����Խṹ��������������Ҫȷ���������˳��
//�����򴴽��Ͳ��򴴽�����

//���򴴽���������Ҫһ���������д洢���ĵ�ַ
/*
	1.����һ�����ݣ���Ϊ0��˵���ǿ���������NULL����Ϊ��0��������㣬�洢���ݣ�ͬʱ������ַ�������
	2.�����в�Ϊ�գ�ȡ��һ����㣬����������������Һ��ӣ�
		������������Ϊ0��������ΪNULL�����������ӣ�ͬʱ����ַ�������
		�ٴζ������ݣ�
		������������Ϊ0���Һ�����ΪNULL���������Һ��ӣ�ͬʱ����ַ�������
	3.�ظ�2��ֱ������Ϊ��
*/

//������������
//�������У�A B C D F G I 0 E 0 0 H 0 0 0 0 0 0
#define Noinfo 0 //��0��ʾû�н��

Bintree create_BT()
{
	elemtype data;
	Bintree BT, T;
	Queue Q = create_Q(100);

	//������һ����㣬�����ڵ�
	scanf("%d", &data);
	if (data != Noinfo) {
		BT = (Bintree)malloc(sizeof(struct BTnode));
		BT->data = data;
		BT->left = NULL;
		BT->right = NULL;
		add_Q(Q, BT);
	}
	else {
		return NULL;
	}

	while (!is_empty_Q(Q)) {
		T = delete_Q(Q);

		scanf("%d", &data);//��������
		if (data == Noinfo) {
			return NULL;
		}
		else {
			T->left = (Bintree)malloc(sizeof(struct BTnode));
			T->left->data = data;
			T->left->left = NULL;
			T->left->right = NULL;
			add_Q(Q, T->left);
		}

		//�����Һ���
		scanf("%d",&data);
		if (data == Noinfo) {
			return NULL;
		}
		else {
			T->right = (Bintree)malloc(sizeof(struct BTnode));
			T->right->data = data;
			T->right->left = NULL;
			T->right->right = NULL;
			add_Q(Q, T->right);
		}
	}

	return BT;
}

//������������

