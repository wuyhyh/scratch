#pragma once
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
typedef double elemtype;

typedef int position;
typedef struct Snode* p_to_stack;
typedef struct Snode {
	elemtype* data;//存放数据的地址
	int maxsize;//最大容量
	position top;//栈顶指针，一般初始化在低地址的地方
}S;
typedef p_to_stack Stack;

Stack create_s(int maxsize);
bool is_full(Stack S);
bool push(Stack S, elemtype x);
bool is_empty(Stack S);
elemtype pop(Stack S);
