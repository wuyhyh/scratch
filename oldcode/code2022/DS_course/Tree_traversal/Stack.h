#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"tree.h"

typedef struct Tnode* elemtype;

typedef struct Snode* ptr_to_Stack;
struct Snode {
	elemtype* data;
	int maxsize;
	int top;
};
typedef ptr_to_Stack Stack;

Stack create_Stack(int maxsize)
{
	Stack S = (Stack)malloc(sizeof(struct Snode));
	S->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	S->maxsize = maxsize;
	S->top = -1;//约定栈顶指针放在小地址
	return S;
}

bool is_empty_Stack(Stack S)
{
	return S->top == -1;
}

bool is_full_Stack(Stack S)
{
	return S->top == (S->maxsize - 1);
}

bool push(Stack S, elemtype e)
{
	if (is_full_Stack(S)) {
		printf("Stack is full\n");
		return false;
	}
	else {
		S->data[++S->top] = e;
		return true;
	}
}

elemtype pop(Stack S)
{
	if (is_empty_Stack(S)) {
		printf("Stack is empty\n");
		return NULL;
	}
	else {
		return S->data[S->top--];
	}
}
