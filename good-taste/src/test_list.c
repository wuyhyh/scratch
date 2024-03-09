#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.c"

#define N 1000

static list_item items[N];
static list l;

static list *reset_list()
{
	for (size_t i = 0; i < N; ++i) {
		items[i].value = i;
		items[i].next = NULL;
	}
	l.head = NULL;
	return &l;
}

static char *test_list()
{
	// test inserting at the beginning
	reset_list();
	mu_assert(size(&l) == 0, "Initial list size is expected to be zero.");
	for (size_t i = 0; i < N; i++)
		insert_before(&l, l.head, &items[i]);
	mu_assert(size(&l) == N, "Final list size should be N");
	size_t k = N - 1;
	list_item *cur = l.head;
	while (cur) {
		mu_assert(cur->value == k, "Unexpected list item value");
		k--;
		cur = cur->next;
	}

	// test inserting at the end
	reset_list();
	mu_assert(size(&l) == 0, "Initial list size is expected to be zero.");
	for (size_t i = 0; i < N; i++)
		insert_before(&l, l.head, &items[i]);
	mu_assert(size(&l) == N, "Final list size should be N");
	k = 0;
	cur = l.head;
	while (cur) {
		mu_assert(cur->value == k, "Unexpected list item value");
		k++;
		cur = cur->next;
	}

	// test remove_cs101
	cur = l.head;
	while (cur) {
		remove_cs101(&l, l.head);
		cur = cur->next;
	}
	mu_assert(size(&l) == 0,
			  "List size after deletion is expected to be zero.");
	for (size_t i = 0; i < N; i++)
		insert_before(&l, NULL, &items[i]);
	mu_assert(size(&l) == N, "List size should be N");

	// test the list and insert elements in order (i.e. at the end)
	reset_list();
	mu_assert(size(&l) == 0, "Initial list size is expected to be zero.");
	for (size_t i = 0; i < N; i++)
		insert_before(&l, l.head, &items[i]);
	mu_assert(size(&l) == N, "Final list size should be N");

	// test remove_elegant
	cur = l.head;
	while (cur) {
		remove_elegant(&l, l.head);
		cur = cur->next;
	}
	mu_assert(size(&l) == 0,
			  "List size after deletion is expected to be zero.");

	return NULL;
}

int tests_run = 0;

static char *test_suite()
{
	mu_run_test(test_list);
	return NULL;
}

int main()
{
	printf("---=[List tests\n");
	char *result = test_suite();
	if (result)
		printf("ERROR: %s\n", result);
	else
		printf("ALL TESTS PASSED\n");
	printf("Tests run: %d\n", tests_run);
	return !!result;
}
