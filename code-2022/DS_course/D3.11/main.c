//栈的实现
//Stack ADT
//数据对象集：0个或多个元素的有穷线性表
//操作集：5个：
/*
	Stack create_s(int maxsize);
    bool is_full(Stack S);
	bool push(Stack S, elemtype x);
	bool is_empty(Stack S);
	elemtype pop(Stack S);
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//顺序栈
typedef int elemtype;

typedef int position;
typedef struct Snode* p_to_stack;
typedef struct Snode {
	elemtype* data;//存放数据的地址
	int maxsize;//最大容量
	position top;//栈顶指针，一般初始化在低地址的地方
}S;
typedef p_to_stack Stack;

Stack create_s(int maxsize)
{
	Stack S = (Stack)malloc(sizeof(struct Snode));//先分配一个结构体的空间
	S->data = (elemtype*)malloc(maxsize * sizeof(elemtype));//再分配存放数据的空间
	S->top = -1;//栈顶指针初始化为-1
	S->maxsize = maxsize;
	return S;
}

bool is_full(Stack S)
{
	if (S->top == S->maxsize - 1)
		return true;
	else
		return false;
}

bool push(Stack S, elemtype x)
{
	if (is_full(S)) {
		printf("栈已满\n");
		return false;
	}
	else {
		S->data[++S->top] = x;//先移动指针再放值进去
		return true;
	}
}

bool is_empty(Stack S)
{
	if (S->top == -1)
		return true;
	else
		return false;
}

elemtype pop(Stack S)
{
	if (is_empty(S)) {
		printf("栈已空\n");
		return;
	}
	else {
		return S->data[S->top--];//先把值吐出来再移动指针
	}
}
