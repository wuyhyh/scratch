//
// Created by wyh on 2023/9/30.
//

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int val)
		: val(val)
		, next(nullptr)
	{
		/* doing nothing */
	}
};

class Solution {
public:
	ListNode *reverseList(ListNode *head)
	{
		ListNode *tmp;
		ListNode *cur = head;
		ListNode *pre = nullptr; // 在你的脑海里面想像一下
		while (cur) {
			tmp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = tmp;
		}
		return pre;
	}
};