//����Queue ADT
//Queue��һ��FIFO���Ա�
//���ݶ��󼯣�0����������Ԫ����ɵ����Ա�
//��������5��
/*
Queue create_q(int maxsize);
bool is_full(Queue Q);
bool add_q(Queue Q, elemtype x);
bool is_empty(Queue Q);
elemtype delete_q(Queue Q);
*/
//ʹ����������ļ��������->ʹ��%����ʵ��ѭ����������һ����λ��ʾ�Ѿ�������Ϊ״̬����

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//ʹ������ʵ��ѭ������
typedef int elemtype;

typedef int position;
typedef struct Qnode* p_to_Qnode;
typedef struct Qnode {
	elemtype* data;//�������
	position front;//��ͷ
	position rear;//��β
	int maxsize;//���Ԫ�ظ���
}Q;
typedef p_to_Qnode Queue;

Queue create_q(int maxsize)
{
	Queue Q = (Queue)malloc(sizeof(struct Qnode));
	Q->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	Q->front = 0;//��ͷ��β����ʼ��Ϊ0
	Q->rear = 0;
	Q->maxsize = maxsize;
}

bool is_full(Queue Q)
{
	return (Q->rear + 1) % (Q->maxsize) == (Q->front);//���һ����λ��Ϊ������
}

bool add_q(Queue Q, elemtype x)
{
	if (is_full(Q)) {
		printf("Queue ��\n");
		return false;
	}
	else {
		Q->rear = (Q->rear + 1) % (Q->maxsize);//��׼����Ҫ�����λ��
		Q->data[Q->rear] = x;
		return true;
	}
}

bool is_empty(Queue Q)
{
	return Q->front == Q->rear;
}

#define ERROR 1e9
elemtype delete_q(Queue Q) 
{
	if (is_empty(Q)) {
		printf("Queue ��\n");
		return ERROR;
	}
	else {
		Q->front = (Q->front + 1) % (Q->maxsize);//�ڶ������棬Ҫ��ջ��Ԫ���Ǹ���front�ĺ����
		return Q->data[Q->front];
	}
}
