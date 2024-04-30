#include"stack.h"

Stack create_s(int maxsize)
{
	Stack S = NULL;
	S = (Stack)malloc(sizeof(struct Snode));//�ȷ���һ���ṹ��Ŀռ�
	S->data = (elemtype*)malloc(maxsize * sizeof(elemtype));//�ٷ��������ݵĿռ�
	S->top = -1;//ջ��ָ���ʼ��Ϊ-1
	S->maxsize = maxsize;
	return S;
}

bool is_full(Stack S)//������ǵĲ�ʹ��ѵ�ǣ�if-else�ṹ�������ǿ��ܳ������
{
	if (S->top == (S->maxsize - 1))
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
	return (S->top == -1);
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
