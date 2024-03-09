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
typedef int elemtype;

typedef int position;
typedef struct Snode* p_to_stack;
typedef struct Snode {
	elemtype* data;//������ݵĵ�ַ
	int maxsize;//�������
	position top;//ջ��ָ�룬һ���ʼ���ڵ͵�ַ�ĵط�
}S;
typedef p_to_stack Stack;

Stack create_s(int maxsize)
{
	Stack S = (Stack)malloc(sizeof(struct Snode));//�ȷ���һ���ṹ��Ŀռ�
	S->data = (elemtype*)malloc(maxsize * sizeof(elemtype));//�ٷ��������ݵĿռ�
	S->top = -1;//ջ��ָ���ʼ��Ϊ-1
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
		printf("ջ����\n");
		return false;
	}
	else {
		S->data[++S->top] = x;//���ƶ�ָ���ٷ�ֵ��ȥ
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
		printf("ջ�ѿ�\n");
		return;
	}
	else {
		return S->data[S->top--];//�Ȱ�ֵ�³������ƶ�ָ��
	}
}
