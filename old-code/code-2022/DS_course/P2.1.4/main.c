//线性表 ADT
/*
类型名称：线性表(List)
数据对象集：n>=0 个元素构成的有限序列<a1,a2,...aN>，前驱后继构成一对一的邻接逻辑关系
操作集：一个具体的表 L 属于 List,表示位置的整数i,一个元素x 属于 elem_type
	  List make_empty();//初始化一个空表
	  List find_kth(List L,int k);//返回位置k的元素
	  position find(List L,elem_type x);//第一次出现的位置
	  List insert(List L,int i,elem_type x);
	  List delete(List L,int i);
	  int lenght(List L);
*/

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

typedef int elem_type;
typedef struct Lnode* List;
typedef struct Lnode {
	elem_type data;
	List next;//下一个元素的位置
}L,*position;

int length(List L)
{
	int cnt = 0;//计数器
	position p = L;//p指向第一个结点
	while (p!=NULL) {
		p = p->next;
		cnt++;
	}
	return cnt;
}

List find_kth(List L, int k)//返回第k个元素ak的地址
{
	int cnt = 1;
	position p = L;//指向表头
	while (p != NULL && cnt < k) {
		p = p->next;
		cnt++;
	}//退出循环有两种可能
	if (cnt == k)
		return p;//返回的是kth结点的地址
	else
		return NULL;//没找到
}

position find(List L, elem_type x)//第一次出现的位置
{
	int cnt = 1;
	position p = L;
	while (p != NULL && p->data != x) {//不断向后移动
		p = p->next;
	}
	if (p != NULL)
		return p;
	else
	return NULL;//没找到
}

//1. 先找到第i-1个结点 2.再找到要删除的结点i 3.修改指针绕过i 4.free i的空间
List delete_l(List L, int i)//删除1<=i<=n个位置的结点
{
	if (i == 1) {//在第一个位置要特殊处理
		if (L == NULL) {
			return NULL;//没有可以删除的
		}
		else {
			List tmp = L;//锁定目标
			L = L->next;//绕过
			free(tmp);//释放删除完成
			return L;
		}
	}

	List pre = find_kth(L, i - 1);
	if (pre == NULL) {
		printf("第%d个结点不存在\n", i - 1);
		return NULL;
	}
	else if (pre->next == NULL) {
		printf("第%d个结点不存在\n", i);
		return NULL;
	}
	else {
		List tmp = pre->next;//锁定目标
		pre->next = tmp->next;//绕过
		free(tmp);//释放删除完成
		return L;
	}
}

List reverse(List L)
{
	List tmp, old_head, new_head;
	old_head = L;
	new_head = NULL;
	while (old_head != NULL) {
		tmp = old_head->next;
		old_head->next = new_head;
		new_head = old_head;
		old_head = tmp;
	}
	L = new_head;
	return L;
}

void print_List(List L)
{
	int i = 1;
	for (int i = 1; i <= (length(L)); i++) {
		printf("a%d ", i);
	}
	putchar('\n');
	List p = L;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	putchar('\n');
}

//三步 1.先构造一个新结点分配空间 2.找到i的前一个位置i-1个结点 3.修改指针
List insert(List L, int i, elem_type x)//在第i-1（1<=i<=n+1）个结点后插入一个值为x的结点
{
	List tmp = (List)malloc(sizeof(struct Lnode));//构造新节点
	tmp->data = x;

	if (i == 1) {//在第一个位置插入要特殊处理
		tmp->next = L;//你是新老大了
		return tmp;
	}
	else {
		//先找到第i-1个结点的地址
		List pre = find_kth(L, i - 1);
		if (pre == NULL) {
			printf("参数错\n");
			return NULL;//插入位置不存在失败
		}
		else {
			tmp->next = pre->next;
			pre->next = tmp->next;
			return L;//返回表头表示插入成功
		}
	}
}

int main()
{
	

	return 0;
}