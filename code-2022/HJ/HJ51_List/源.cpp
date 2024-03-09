#include<iostream>
#include<list>
using namespace std;

struct ListNode {
	int m_nKey;
	ListNode* m_pNext;
	ListNode(int x) :m_nKey(x), m_pNext(nullptr) {};//构造函数
};
typedef ListNode* List;


int main()
{
	int num;
	while (cin >> num) {
		List head = new ListNode(-1);
		List ptr = head;
		for (int i = 0; i < num; i++) {
			int a;
			cin >> a;
			List temp = new ListNode(a);//使用头插法
			temp->m_pNext = ptr->m_pNext;
			ptr->m_pNext = temp;
		}
		int k;
		cin >> k;
		if (k <= 0 || k > num) {
			cout << 0 << endl;
			continue;//下一组数据
		}
		for (int i = 1; i <= k; i++) {
			ptr = ptr->m_pNext;
		}
		cout<<ptr->m_nKey<<endl;
	}

	return 0;
}

int main1()
{
	int num = 8;
	List head = new ListNode(-1);
	List ptr = head;
	for (int i = 0; i < num; i++) {
		List temp = new ListNode(i+1);//使用头插法
		temp->m_pNext = ptr->m_pNext;
		ptr->m_pNext = temp;
	}
	ptr = head->m_pNext;
	for (int i = 1; i <= num; i++) {
		cout << ptr->m_nKey << endl;
		ptr = ptr->m_pNext;
	}

	return 0;
}