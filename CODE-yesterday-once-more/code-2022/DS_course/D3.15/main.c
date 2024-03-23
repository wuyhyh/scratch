//堆栈的链表实现
//用链表实现的时候只能在头结点一端操作push、pop
//为了简便算法，设置一个空的头结点作为链表的结点，其后的第一个结点作为栈顶指针指向的结点

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
	temp->next = S->next;//这两行
	S->next = temp;//是链表的插入
	return true;
}

#define ERROR -1
elemtype pop(Stack S)
{
	if (is_empty(S)) {
		printf("stack 空\n");
		return ERROR;
	}
	else {
		Stack pre = S->next;//pre是1号结点，锁定目标
		elemtype e = pre->data;//取出数据
		S->next = pre->next;//绕过
		free(pre);//释放
		return e;
	}
}
