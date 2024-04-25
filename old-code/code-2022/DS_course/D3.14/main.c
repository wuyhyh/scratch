//��һ������ʵ��˫��ջ���������������м�����

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int elemtype;

typedef int position;
typedef struct Dstack_node* p_to_Dstack;
typedef struct Dstack_node {
	elemtype* data;
	position top1;//��ʼ��Ϊ-1
	position top2;//��ʼ��Ϊmaxsize
	int maxsize;
};
typedef p_to_Dstack Dstack;

Dstack create_ds(int maxsize)
{
	Dstack DS = (Dstack)malloc(sizeof(struct Dstack_node));
	DS->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	DS->top1 = -1;
	DS->top2 = maxsize;
	DS->maxsize = maxsize;
}

enum tag{ stack1=1, stack2 };
bool push(Dstack DS, int tag,elemtype x)//tag��Ϊ����������ջ�ı�ʶ,ȡֵΪ1��2
{
	if (DS->top2 - DS->top1 == 1) {//����ָ�����1˵��û��λ����
		printf("��ջ��\n");
		return false;
	}
	else {
		if (tag == stack1)//�������ƶ�ָ���ٰ�ֵ�Ž�ȥ
			DS->data[++DS->top1] = x;
		else
			DS->data[--DS->top2] = x;
		return true;
	}
}

elemtype pop(Dstack DS, int tag)
{
	if (tag == stack1) {//stack1
		if (DS->top1 == -1) {
			printf("stack1 ��\n");
			return;
		}
		else {
			return DS->data[DS->top1--];
		}
	}
	else {//stack2
		if (DS->top2 == DS->maxsize) {
			printf("stack2 ��\n");
			return;
		}
		else {
			DS->data[DS->top2++];
		}
	}
}
