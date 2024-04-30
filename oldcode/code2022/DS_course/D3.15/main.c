//��ջ������ʵ��
//������ʵ�ֵ�ʱ��ֻ����ͷ���һ�˲���push��pop
//Ϊ�˼���㷨������һ���յ�ͷ�����Ϊ����Ľ�㣬���ĵ�һ�������Ϊջ��ָ��ָ��Ľ��

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

typedef int elemtype;

typedef struct Snode* p_to_Snode;
typedef struct Snode {
	elemtype data;
	p_to_Snode next;
};
typedef p_to_Snode Stack;

Stack create_s()
{
	Stack S = (Stack)malloc(sizeof(struct Snode));
	S->next = NULL;
	return S;
}

bool is_empty(Stack S)
{
	if (S->next == NULL)
		return true;
}

bool push(Stack S, elemtype x)
{
	Stack temp = NULL;
	temp = (Stack)malloc(sizeof(struct Snode));
	temp->data = x;
	temp->next = S->next;//������
	S->next = temp;//������Ĳ���
	return true;
}

#define ERROR -1
elemtype pop(Stack S)
{
	if (is_empty(S)) {
		printf("stack ��\n");
		return ERROR;
	}
	else {
		Stack pre = S->next;//pre��1�Ž�㣬����Ŀ��
		elemtype e = pre->data;//ȡ������
		S->next = pre->next;//�ƹ�
		free(pre);//�ͷ�
		return e;
	}
}
