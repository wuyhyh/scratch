//用链表实现Queue，由于链表的特性，只能在链表的尾部add,在链表的头部删除。

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef int elemtype;

//这个链表存放了队列的数据
typedef struct Node* p_to_Node;
typedef struct Node {//队列中的结点
	elemtype data;
	p_to_Node next;
};
typedef p_to_Node position;

//用队列的接口去访问链表
typedef struct Qnode* p_to_Qnode;
struct Qnode {//队列
	position front;
	position rear;
	int maxsize;//这个似乎没有意义
};
typedef p_to_Qnode Queue;

bool is_empty(Queue Q)
{
	return Q->front == NULL;//front没有指向一个链表，链表不存在，是个nullptr
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
		printf("Queue 空\n");
		return ERROR;
	}
	else {
		position pre = Q->front;
		if (Q->front == Q->rear)//如果队列中只有一个元素
			Q->front = Q->rear = NULL;//删除后队列置为空
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
		printf("Queue 空\n");
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
