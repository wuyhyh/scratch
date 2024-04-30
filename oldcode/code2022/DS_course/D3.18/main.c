//������ʵ��Queue��������������ԣ�ֻ���������β��add,�������ͷ��ɾ����

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef int elemtype;

//����������˶��е�����
typedef struct Node* p_to_Node;
typedef struct Node {//�����еĽ��
	elemtype data;
	p_to_Node next;
};
typedef p_to_Node position;

//�ö��еĽӿ�ȥ��������
typedef struct Qnode* p_to_Qnode;
struct Qnode {//����
	position front;
	position rear;
	int maxsize;//����ƺ�û������
};
typedef p_to_Qnode Queue;

bool is_empty(Queue Q)
{
	return Q->front == NULL;//frontû��ָ��һ�������������ڣ��Ǹ�nullptr
}

void add_q(Queue Q, elemtype x)
{
	position temp = (position)malloc(sizeof(struct Node));
	temp->data = x;
	temp->next = NULL;

	Q->rear = temp;
}

#define ERROR 1e9
elemtype delete_q(Queue Q)
{
	if (is_empty(Q)) {
		printf("Queue ��\n");
		return ERROR;
	}
	else {
		position pre = Q->front;
		if (Q->front == Q->rear)//���������ֻ��һ��Ԫ��
			Q->front = Q->rear = NULL;//ɾ���������Ϊ��
		else
			Q->front = pre->next;

		elemtype e = pre->data;
		free(pre);
		return e;
	}
}

void print_q(Queue Q)
{
	if (is_empty(Q)) {
		printf("Queue ��\n");
		return;
	}
	else {
		while (Q->front != NULL) {
			printf("%d ", Q->front->data);
			Q->front = Q->front->next;
		}
	}
}

int main()
{
	Queue Q = (Queue)malloc(sizeof(struct Qnode));
	add_q(Q, 12);
	add_q(Q, 3);
	add_q(Q, 45);
	add_q(Q, 6);
	print_q(Q);


	return 0;
}
