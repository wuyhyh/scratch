//用一个数组实现双堆栈，从数组两端向中间生长

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int elemtype;

typedef int position;
typedef struct Dstack_node* p_to_Dstack;
typedef struct Dstack_node {
	elemtype* data;
	position top1;//初始化为-1
	position top2;//初始化为maxsize
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
bool push(Dstack DS, int tag,elemtype x)//tag作为区分两个堆栈的标识,取值为1、2
{
	if (DS->top2 - DS->top1 == 1) {//两个指针相差1说明没有位置了
		printf("堆栈满\n");
		return false;
	}
	else {
		if (tag == stack1)//都是先移动指针再把值放进去
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
			printf("stack1 空\n");
			return;
		}
		else {
			return DS->data[DS->top1--];
		}
	}
	else {//stack2
		if (DS->top2 == DS->maxsize) {
			printf("stack2 空\n");
			return;
		}
		else {
			DS->data[DS->top2++];
		}
	}
}
