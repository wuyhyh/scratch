#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef int elemtype;

typedef struct Lnode* ptr_to_Lnode;
struct Lnode {
	elemtype* data;//ָ�������ݵĿռ�
	int maxsize;
	int last;//���һ��Ԫ���������λ��
};
typedef ptr_to_Lnode List;//ʹ��ָ����ʺʹ���˳����Ǹ�Ч��

#define MAXSIZE 100
List create_List(int maxsize)
{
	List L = (List)malloc(sizeof(struct Lnode));
	L->data = (elemtype*)malloc(maxsize * sizeof(elemtype));
	L->maxsize = maxsize;
	L->last = -1;
}

int length(List L)
{
	return L->last + 1;
}

int find(List L, elemtype e)
{
	int i;
	for (i = 0; i <= L->last; i++)
	{
		if (L->data[i] == e)
			return i + 1;
	}

	return -1;//not find
}

elemtype find_Kth(List L, int k)
{
	if (k<1 || k>L->last + 1) {
		printf("out of boundary\n");
		return INT_MAX;
	}
	else {
		return L->data[k - 1];
	}
}

bool insert_List(List L, int k, elemtype e)
{
	if (L->last == L->maxsize - 1) {
		printf("List is full\n");
		return false;
	}

	if (k<1 || k>L->last + 2) {
		printf("out of boundary\n");
		return false;
	}
	else {
		int i;
		for (i = L->last; i >= k-1; i--) {//ע��ÿһ���±궼Ҫ���ݵ�����ν�ı߽�����
			L->data[i + 1] = L->data[i];
		}
		L->data[k - 1] = e;
		L->last++;
		return true;
	}
}

bool delete_List(List L, int k)
{
	if (k<1 || k>L->last + 1) {
		printf("out of bounday\n");
		return false;
	}
	else {
		int i;
		for (i = k - 1; i < L->last; i++) {
			L->data[i] = L->data[i + 1];
		}
		L->last--;//Ҫ��סlastҪ����
		return true;
	}
}

void print_List(List L)
{
	for (int i = 0; i <= L->last; i++) {
		printf("%d ", L->data[i]);
	}
	putchar('\n');
}

int main()
{
	List ss = create_List(100);
	for(int i=0;i<10;i++)
		insert_List(ss, 1, rand()%120);
	print_List(ss);
	insert_List(ss, 5, 1000);
	print_List(ss);
	delete_List(ss, 8);
	print_List(ss);
	printf("%d \n", find_Kth(ss, 3));
	printf("%d\n", length(ss));
	printf("%d \n", find(ss, 78));

	return 0;
}