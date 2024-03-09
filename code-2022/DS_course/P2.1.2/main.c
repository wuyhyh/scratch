//线性表 ADT
/*
类型名称：线性表(List)
数据对象集：n>=0 个元素构成的有限序列<a1,a2,...aN>，前驱后继构成一对一的邻接逻辑关系
操作集：一个具体的表 L 属于 List,表示位置的整数i,一个元素x 属于 elem_type
	  List make_empty();//初始化一个空表
	  elem_type find_kth(List L,int i);//返回位置k的元素
	  position find(List L,elem_type x);//第一次出现的位置
	  bool insert(List L,int i,elem_type x);
	  bool delete(List L,int i);
	  int lenght(List L);
*/

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>

#define MAXSIZE 100
typedef int elem_type;
typedef int position;
typedef struct Lnode {
	elem_type data[MAXSIZE];
	position last;//最后一个元素的位置
}L, * List;

List make_empty()//初始化一个空表
{
	List ptrL;
	ptrL = (List)malloc(sizeof(struct Lnode));
	ptrL->last = -1;
	return ptrL;
}

elem_type find_kth(List L, int i)//返回位置k的元素
{
	return L->data[i - 1];//ai放在data[i-1]处
}

position find(List L, elem_type x)//第一次出现的位置
{
	position j = 0;
	while (j <= L->last && x != L->data[j]) {
		j++;
	}//退出循环可能有两种情况
	if (j > L->last)
		return -1;//没有找到
	else
		return j;
}

bool insert(List L, int i, elem_type x)//在位置1<=i<=n+1插入x，特别注意i是序列的下标
{
	if (L->last == MAXSIZE - 1) {//如果表满，退出
		printf("表满\n");
		return false;
	}
	if (i<1 || i>L->last + 2) {//last=n-1,看看位置是不是在1~n+1
		printf("位置不合法\n");
		return false;
	}

	int j;//j表示的是数组下标，而i是序列的下标，ai放在data[i-1]处
	for (j = L->last; j >= i - 1; j--) {
		L->data[j + 1] = L->data[j];//依次移动an~ai
	}
	L->data[i - 1] = x;//in a nutshell，你需要移动数组下标为i-1到last的所有元素，然后把x放到i-1处，增加last的值
	L->last++;
	return true;
}

bool delete_l(List L, int i)//1<=i<=n
{
	if (i<1 || i>L->last + 1) {
		printf("不存在第%d个元素\n", i);
		return false;
	}
	//elem_type temp = L->data[i - 1];//直接覆盖了
	for (int j = i; j <= L->last; j++) {
		L->data[j - 1] = L->data[j];
	}
	L->last--;
	return true;
}

int length(List L)
{
	return L->last + 1;//last = n-1
}

void print_List(List L)
{
	int i = 1;
	for (int i = 1; i <= (length(L)); i++) {
		printf("a%-3d ", i);
	}
	putchar('\n');
	for (int i = 0; i < length(L); i++) {
		printf("%-4d ", L->data[i]);
	}
	putchar('\n');
}

int main()
{
	int arr[] = { 5, 3, 9, 9, 5, 10,1,5, 8, 2 };
	List list = make_empty();
	for (int i = 0; i < 10; i++) {
		insert(list, 1, arr[i]);
	}
	print_List(list);
	insert(list, 5, 200);
	print_List(list);
	delete_l(list, 8);
	print_List(list);
	printf("length = %d\n", length(list));
	printf("a%d = %d\n", 9,find_kth(list, 9));
	printf("a%d = %d\n", find(list, 5)+1,5);
}