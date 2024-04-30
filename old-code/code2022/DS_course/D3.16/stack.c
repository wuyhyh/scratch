#include"stack.h"

Stack create_s(int maxsize)
{
	Stack S = NULL;
	S = (Stack)malloc(sizeof(struct Snode));//先分配一个结构体的空间
	S->data = (elemtype*)malloc(maxsize * sizeof(elemtype));//再分配存放数据的空间
	S->top = -1;//栈顶指针初始化为-1
	S->maxsize = maxsize;
	return S;
}

bool is_full(Stack S)//这给我们的惨痛教训是，if-else结构不完整是可能出问题的
{
	if (S->top == (S->maxsize - 1))
		return true;
	else
		return false;
}

bool push(Stack S, elemtype x)
{
	if (is_full(S)) {
		printf("栈已满\n");
		return false;
	}
	else {
		S->data[++S->top] = x;//先移动指针再放值进去
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
		printf("栈已空\n");
		return;
	}
	else {
		return S->data[S->top--];//先把值吐出来再移动指针
	}
}
