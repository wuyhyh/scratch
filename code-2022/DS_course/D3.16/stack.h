#pragma once
//ջ��ʵ��
//Stack ADT
//���ݶ��󼯣�0������Ԫ�ص��������Ա�
//��������5����
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

//˳��ջ
typedef double elemtype;

typedef int position;
typedef struct Snode* p_to_stack;
typedef struct Snode {
	elemtype* data;//������ݵĵ�ַ
	int maxsize;//�������
	position top;//ջ��ָ�룬һ���ʼ���ڵ͵�ַ�ĵط�
}S;
typedef p_to_stack Stack;

Stack create_s(int maxsize);
bool is_full(Stack S);
bool push(Stack S, elemtype x);
bool is_empty(Stack S);
elemtype pop(Stack S);
