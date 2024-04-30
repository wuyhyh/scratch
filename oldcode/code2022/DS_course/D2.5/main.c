//逆转一个单链表
#include<stdio.h>

typedef int elemtype;

typedef struct Lnode* List;
typedef struct Lnode {
	elemtype data;
	List next;
};

List reverse(List L)
{
	List temp, old_head, new_head;
	old_head = L;
	new_head = NULL;

	while (old_head != NULL) {
		temp = old_head->next;
		old_head->next = new_head;
		new_head = old_head;
		old_head = temp;
	}

	return new_head;
}