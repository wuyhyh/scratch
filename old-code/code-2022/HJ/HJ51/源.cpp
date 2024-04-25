//输入一个单向链表，输出该链表中倒数第k个结点，链表的倒数第1个结点为链表的尾指针。
//
//链表结点定义如下：
//struct ListNode
//{
//    int m_nKey;
//    ListNode* m_pNext;
//};
//正常返回倒数第k个结点指针，异常返回空指针.
//要求：
//(1)正序构建链表;
//(2)构建后要忘记链表长度。
//数据范围：链表长度满足 1 \le n \le 1000 \1≤n≤1000  ， k \le n \k≤n  ，链表中数据满足 0 \le val \le 10000 \0≤val≤10000
//
//本题有多组样例输入。

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef struct ListNode* ptr_to_ListNode;
struct ListNode {
	int value;
	ptr_to_ListNode next;
};
typedef ptr_to_ListNode List;

List insert(List L, int e)
{
	List temp = (List)malloc(sizeof(struct ListNode));
	temp->value = e;
	temp->next = NULL;
	if (L == NULL) {
		return temp;
	}
	else {
		temp->next = L->next;
		L->next = temp;
		return temp;
	}
}

int find_Kth(List L,int k)
{
	List curr = L;
	for (int i = 1; i <= k; i++) {
		curr = curr->next;
	}
	return curr->value;
}

List reverse(List L)
{
	List old_head;
	List new_head;
	List temp = NULL;

	old_head = L;
	new_head = NULL;
	while (old_head) {
		temp = old_head->next;
		old_head->next = new_head;
		new_head = old_head;
		old_head = temp;
	}
	L = new_head;
	return L;
}

int main() 
{
	int len;
	cin >> len;
	int num;
	vector<int> values;
	while (cin >> num) {
		values.push_back(num);
	}
	List L = NULL;
	for (int i = 0; i < len-1; i++) {
		L = insert(L, values[i]);
	}
	L = reverse(L);
	cout << find_Kth(L, values[values.size() - 1]);

	return 0;
}