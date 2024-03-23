//
// Created by wyh on 2023/11/12.
//

#include "list.h"

void remove_cs101(list *l, list_item *target)
{
	list_item *cur = l->head, *prev = NULL;
	while (cur != target) {
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		prev->next = cur->next;
	else
		l->head = cur->next;
}

static inline list_item **find_indirect(list *l, list_item *target)
{
	list_item **p = &l->head;
	while (*p != target)
		p = &(*p)->next;
	return p;
}

void remove_elegant(list *l, list_item *target)
{
	list_item **p = find_indirect(l, target);
	*p = target->next;
}

void insert_before(list *l, list_item *before, list_item *item)
{
	list_item **p = find_indirect(l, before);
	*p = item;
	item->next = before;
}

size_t size(list *l)
{
	size_t k = 0;
	list_item *cur = l->head;
	while (cur) {
		cur = cur->next;
		k++;
	}
	return k;
}