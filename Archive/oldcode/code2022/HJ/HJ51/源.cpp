//����һ��������������������е�����k����㣬����ĵ�����1�����Ϊ�����βָ�롣
//
//�����㶨�����£�
//struct ListNode
//{
//    int m_nKey;
//    ListNode* m_pNext;
//};
//�������ص�����k�����ָ�룬�쳣���ؿ�ָ��.
//Ҫ��
//(1)���򹹽�����;
//(2)������Ҫ���������ȡ�
//���ݷ�Χ������������ 1 \le n \le 1000 \1��n��1000  �� k \le n \k��n  ���������������� 0 \le val \le 10000 \0��val��10000
//
//�����ж����������롣

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