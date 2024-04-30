//���Ա� ADT
/*
�������ƣ����Ա�(List)
���ݶ��󼯣�n>=0 ��Ԫ�ع��ɵ���������<a1,a2,...aN>��ǰ����̹���һ��һ���ڽ��߼���ϵ
��������һ������ı� L ���� List,��ʾλ�õ�����i,һ��Ԫ��x ���� elem_type
	  List make_empty();//��ʼ��һ���ձ�
	  elem_type find_kth(List L,int i);//����λ��k��Ԫ��
	  position find(List L,elem_type x);//��һ�γ��ֵ�λ��
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
	position last;//���һ��Ԫ�ص�λ��
}L, * List;

List make_empty()//��ʼ��һ���ձ�
{
	List ptrL;
	ptrL = (List)malloc(sizeof(struct Lnode));
	ptrL->last = -1;
	return ptrL;
}

elem_type find_kth(List L, int i)//����λ��k��Ԫ��
{
	return L->data[i - 1];//ai����data[i-1]��
}

position find(List L, elem_type x)//��һ�γ��ֵ�λ��
{
	position j = 0;
	while (j <= L->last && x != L->data[j]) {
		j++;
	}//�˳�ѭ���������������
	if (j > L->last)
		return -1;//û���ҵ�
	else
		return j;
}

bool insert(List L, int i, elem_type x)//��λ��1<=i<=n+1����x���ر�ע��i�����е��±�
{
	if (L->last == MAXSIZE - 1) {//����������˳�
		printf("����\n");
		return false;
	}
	if (i<1 || i>L->last + 2) {//last=n-1,����λ���ǲ�����1~n+1
		printf("λ�ò��Ϸ�\n");
		return false;
	}

	int j;//j��ʾ���������±꣬��i�����е��±꣬ai����data[i-1]��
	for (j = L->last; j >= i - 1; j--) {
		L->data[j + 1] = L->data[j];//�����ƶ�an~ai
	}
	L->data[i - 1] = x;//in a nutshell������Ҫ�ƶ������±�Ϊi-1��last������Ԫ�أ�Ȼ���x�ŵ�i-1��������last��ֵ
	L->last++;
	return true;
}

bool delete_l(List L, int i)//1<=i<=n
{
	if (i<1 || i>L->last + 1) {
		printf("�����ڵ�%d��Ԫ��\n", i);
		return false;
	}
	//elem_type temp = L->data[i - 1];//ֱ�Ӹ�����
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