//二叉树的链式存储

//二叉树ADT
/*
	数据集：有穷的结点的集合。这个集合可以为空，非空的话，由一个根节点和他的左右子树构成。
	操作集：
	1.create
	2.is_empty
	3.traversal//遍历
*/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int elemtype;

typedef struct BTnode* p_to_BTnode;
typedef p_to_BTnode Bintree;
struct BTnode {
	elemtype data;//数据域和指向左右孩子的指针
	Bintree left;
	Bintree right;
};

//中序:左根右
void inorder_traversal(Bintree BT)
{
	if (BT) {
		inorder_traversal(BT->left);
		printf("%d ", BT->data);
		inorder_traversal(BT->right);
	}
}

//先序：根左右
void preorder_traversal(Bintree BT)
{
	if (BT) {
		printf("%d ", BT->data);
		preorder_traversal(BT->left);
		preorder_traversal(BT->right);
	}
}

//后序：左右根
void postorder_traversal(Bintree BT)
{
	if (BT) {
		postorder_traversal(BT->left);
		postorder_traversal(BT->right);
		printf("%d ", BT->data);
	}
}

//非递归遍历
/*
	递归遍历的代码很简洁但是效率不高，递归本质是利用栈实现的，我们不让中间商赚差价，直接借助堆栈实现非递归遍历
	中序、先序、后序遍历时经过结点的顺序是一样的，只是访问的时机不一样
	先序和中序的非递归要简单一点，后序遍历则要两次将一个元素入栈，要复杂一点
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

//中序遍历的非递归实现
//左根右
/*
	1.遇到一个结点把他压入栈，去访问他的左子树，直到左子树访问完
	2.左子树访问完后，从栈里面弹出来，访问他
	3.再去遍历右子树
*/

void inorder_tra(Bintree BT)
{
	Stack S = create_S();
	Bintree T = BT;

	while (T || !is_empty_S(S)) {//树和栈都是非空的
		while (T) {//一路向左
			push(S, T);
			T = T->left;
		}
		T = pop(S);//弹出并访问
		printf("%d ", T->data);
		T = T->right;//转向右子树
	}
}

void preorder_tra(Bintree BT);

void postorder_tra(Bintree BT);

/*
	二叉树遍历的核心问题是把一个二维结构线性化为一个序列
	关键是借助一个存储结构来保存暂不访问的结点
	用Stack可以实现先序、中序、后序访问，用Queue实现层序访问
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
		Q->front = (Q->front + 1) % Q->maxsize;//Q->front进行了移动
		return Q->data[Q->front];
	}
}

//层序遍历：一层一层地访问
/*
	借助队列来实现：
	1.从队列中取出一个元素
	2.访问他
	3.如果这个元素有左右孩子，把他的孩子放入队列
*/

void level_order_traversal(Bintree BT)
{
	if (!BT)
		return;//空树直接返回

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

//输出所有叶节点
void preorder_print_leaves(Bintree BT)
{
	if (BT) {
		if ((!BT->left) && (!BT->right)) {//如果是叶节点
			printf("%d ", BT->data);
		}
		preorder_print_leaves(BT->left);
		preorder_print_leaves(BT->right);
	}
}

//求二叉树的高度
//Height = max{H_left,H_right}+1;//也是递归，使用后序遍历，因为要先知道左右子树的高度
int get_height(Bintree BT)
{
	int Hl, Hr, maxH;

	if (BT) {
		Hl = get_height(BT->left);
		Hr = get_height(BT->right);
		maxH = (Hl > Hr) ? Hl : Hr;
		return maxH + 1;//这是尾递归
	}
	return 0;
}

//二叉树的生成
//二叉树是非线性结构，创建二叉树需要确定输入结点的顺序
//有先序创建和层序创建两种

//层序创建二叉树需要一个辅助队列存储结点的地址
/*
	1.输入一个数据，若为0，说明是空树，返回NULL；若为非0，创建结点，存储数据，同时将结点地址放入队列
	2.若队列不为空，取出一个结点，并建立这个结点的左右孩子：
		如果输入的数据为0，左孩子置为NULL，否则建立左孩子，同时将地址放入队列
		再次读入数据：
		如果输入的数据为0，右孩子置为NULL，否则建立右孩子，同时将地址放入队列
	3.重复2，直到队列为空
*/

//层序建立二叉树
//输入序列：A B C D F G I 0 E 0 0 H 0 0 0 0 0 0
#define Noinfo 0 //用0表示没有结点

Bintree create_BT()
{
	elemtype data;
	Bintree BT, T;
	Queue Q = create_Q(100);

	//建立第一个结点，即根节点
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

		scanf("%d", &data);//读入左孩子
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

		//读入右孩子
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

//先序建立二叉树

