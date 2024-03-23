//
// Created by wyh on 2023/9/29.
//

#include <cstdio>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x)
		: val(x)
		, next(nullptr)
	{
		/* doing nothing */
	}
};

class Solution {
public:
	ListNode *removeElements(ListNode *head, int val)
	{
		// 删除头结点
		while (head != NULL && head->val == val) {
			ListNode *tmp = head;
			head = head->next;
			delete tmp;
		}

		// 删除非头结点
		ListNode *cur = head;
		while (cur != NULL && cur->next != NULL) {
			if (cur->next->val == val) {
				ListNode *tmp = cur->next;
				cur->next = cur->next->next;
				delete tmp;
			} else {
				cur = cur->next;
			}
		}
		return head;
	}
};
