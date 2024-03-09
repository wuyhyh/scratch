#include<stdio.h>

typedef int elemtype;

typedef struct Lnode* List;
typedef struct Lnode {
	elemtype data;
	List next;
};

//嵌套循环
//求单链表L中所有结点的阶乘和
int factorial_sum(List L)
{
	int fact, sum = 0;
	List p = L;

	while (p != NULL) {
		fact = 1;
		for (int i = 1; i <= p->data; i++) {
			fact *= i;
		}
		sum += fact;
		p = p->next;
	}
	return sum;
}
