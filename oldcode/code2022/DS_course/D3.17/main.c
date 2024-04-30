//队列Queue ADT
//Queue是一种FIFO线性表
//数据对象集：0个或多个有穷元素组成的线性表
//操作集：5个
/*
Queue create_q(int maxsize);
bool is_full(Queue Q);
bool add_q(Queue Q, elemtype x);
bool is_empty(Queue Q);
elemtype delete_q(Queue Q);
*/
//使用数组带来的假溢出现象->使用%运算实现循环链表，留出一个空位表示已经满了作为状态区分

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//使用数组实现循环链表
typedef int elemtype;

typedef int position;
typedef struct Qnode* p_to_Qnode;
typedef struct Qnode {
	elemtype* data;//存放数据
	position front;//队头
	position rear;//队尾
	int maxsize;//最大元素个数
}Q;
typedef p_to_Qnode Queue;

Queue create_q(int maxsize)
{
	Queue Q = (Queue)malloc(sizeof(struct Qnode));
	Q->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	Q->front = 0;//队头队尾都初始化为0
	Q->rear = 0;
	Q->maxsize = maxsize;
}

bool is_full(Queue Q)
{
	return (Q->rear + 1) % (Q->maxsize) == (Q->front);//相距一个单位认为就满了
}

bool add_q(Queue Q, elemtype x)
{
	if (is_full(Q)) {
		printf("Queue 满\n");
		return false;
	}
	else {
		Q->rear = (Q->rear + 1) % (Q->maxsize);//先准备好要放入的位置
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
		printf("Queue 空\n");
		return ERROR;
	}
	else {
		Q->front = (Q->front + 1) % (Q->maxsize);//在队列里面，要出栈的元素是跟在front的后面的
		return Q->data[Q->front];
	}
}
