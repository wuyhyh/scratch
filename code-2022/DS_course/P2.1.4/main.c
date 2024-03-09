//���Ա� ADT
/*
�������ƣ����Ա�(List)
���ݶ��󼯣�n>=0 ��Ԫ�ع��ɵ���������<a1,a2,...aN>��ǰ����̹���һ��һ���ڽ��߼���ϵ
��������һ������ı� L ���� List,��ʾλ�õ�����i,һ��Ԫ��x ���� elem_type
	  List make_empty();//��ʼ��һ���ձ�
	  List find_kth(List L,int k);//����λ��k��Ԫ��
	  position find(List L,elem_type x);//��һ�γ��ֵ�λ��
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
	List next;//��һ��Ԫ�ص�λ��
}L,*position;

int length(List L)
{
	int cnt = 0;//������
	position p = L;//pָ���һ�����
	while (p!=NULL) {
		p = p->next;
		cnt++;
	}
	return cnt;
}

List find_kth(List L, int k)//���ص�k��Ԫ��ak�ĵ�ַ
{
	int cnt = 1;
	position p = L;//ָ���ͷ
	while (p != NULL && cnt < k) {
		p = p->next;
		cnt++;
	}//�˳�ѭ�������ֿ���
	if (cnt == k)
		return p;//���ص���kth���ĵ�ַ
	else
		return NULL;//û�ҵ�
}

position find(List L, elem_type x)//��һ�γ��ֵ�λ��
{
	int cnt = 1;
	position p = L;
	while (p != NULL && p->data != x) {//��������ƶ�
		p = p->next;
	}
	if (p != NULL)
		return p;
	else
	return NULL;//û�ҵ�
}

//1. ���ҵ���i-1����� 2.���ҵ�Ҫɾ���Ľ��i 3.�޸�ָ���ƹ�i 4.free i�Ŀռ�
List delete_l(List L, int i)//ɾ��1<=i<=n��λ�õĽ��
{
	if (i == 1) {//�ڵ�һ��λ��Ҫ���⴦��
		if (L == NULL) {
			return NULL;//û�п���ɾ����
		}
		else {
			List tmp = L;//����Ŀ��
			L = L->next;//�ƹ�
			free(tmp);//�ͷ�ɾ�����
			return L;
		}
	}

	List pre = find_kth(L, i - 1);
	if (pre == NULL) {
		printf("��%d����㲻����\n", i - 1);
		return NULL;
	}
	else if (pre->next == NULL) {
		printf("��%d����㲻����\n", i);
		return NULL;
	}
	else {
		List tmp = pre->next;//����Ŀ��
		pre->next = tmp->next;//�ƹ�
		free(tmp);//�ͷ�ɾ�����
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

//���� 1.�ȹ���һ���½�����ռ� 2.�ҵ�i��ǰһ��λ��i-1����� 3.�޸�ָ��
List insert(List L, int i, elem_type x)//�ڵ�i-1��1<=i<=n+1�����������һ��ֵΪx�Ľ��
{
	List tmp = (List)malloc(sizeof(struct Lnode));//�����½ڵ�
	tmp->data = x;

	if (i == 1) {//�ڵ�һ��λ�ò���Ҫ���⴦��
		tmp->next = L;//�������ϴ���
		return tmp;
	}
	else {
		//���ҵ���i-1�����ĵ�ַ
		List pre = find_kth(L, i - 1);
		if (pre == NULL) {
			printf("������\n");
			return NULL;//����λ�ò�����ʧ��
		}
		else {
			tmp->next = pre->next;
			pre->next = tmp->next;
			return L;//���ر�ͷ��ʾ����ɹ�
		}
	}
}

int main()
{
	

	return 0;
}