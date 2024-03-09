
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

typedef int elem_type;
typedef struct Lnode* List;
typedef struct Lnode {
	elem_type data;
	List next;//下一个元素的位置
}L, * position;

typedef struct Qnode {
	position front;
	position rear;
	int maxsize;
}*Queue;

int length(List L)
{
	int cnt = 0;//计数器
	position p = L;//p指向第一个结点
	while (p != NULL) {
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

void print_List(List L)
{
	int i = 1;
	for (int i = 1; i <= (length(L)); i++) {
		printf("a%-3d ", i);
	}
	putchar('\n');
	List p = L;
	while (p != NULL) {
		printf("%-4d ", p->data);
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

bool is_empty_q(Queue Q)
{
	return Q->front == Q->rear;
}

elem_type delete_q(Queue Q)
{
	position temp = delete_l(Q, length(Q)-1);
	return temp->data;
}

Queue add_q(Queue Q, elem_type x)
{
	Q = insert(Q, 1, x);
}

void print_q(Queue Q)
{
	print_List(Q);
}

Queue create_q(List L)
{
	Queue Q = (Queue)malloc(sizeof(struct Qnode));
	Q->front = L;
	Q->rear = find_kth(L, length(L));
	Q->maxsize = length(L);
}

int main()
{
	List L = NULL;
	L = insert(L, 1,10);
	L = insert(L, 1, 2);
	L = insert(L, 1, 4);
	print_List(L);

	Queue Q = NULL;
	Q = add_q(Q, 100);
	printf("%d\n", Q->front->data);
	


	return 0;
}