#pragma once
#include"data_type.h"

//Ͱ����ͻ�������
/*
* Ͱ����Ҫ����֪������Ԫ�ص�ȡֵ��Χ������ȡֵ��Χ��0~M-1,��ô����ҪM��Ͱ��
* Ͱ��ʵ��������Ľ�㣬���ڷ�����ռ�������������
* ���������Ƕ�ؼ�ֵ��Ͱ���򣬱���һ����λ��������λ��ʮλ����λ����������������Ҫ��������Ͱ����
  ������������ظ�����Ͱ�����Կռ���ۻ���O(M).
* һ��أ������d���ؼ��֣���ô��Ҫ����d��Ͱ���򣬷�Ϊ��λ����MSD����λ����LSD��
* �������˿��������ӣ���λ�ǻ�ɫ����λ����ֵ����ôLSDЧ�ʱ�MSDҪ��һ�㣬��ΪLSD���ڷ����ռ����ԣ�MSD���ڷ��β��ԣ��ֱ������ٺϲ����
* �����N���ؼ��֣���ôһ���������ҪN�������M���ռ����ܵ�ʱ����۾���O(d*(N+M));
* �����ֽ����⣺
  ������ǰ�ȡֵ��Χ������Ͱ����ô���ܴ����޴�Ŀռ��˷ѣ������20����������λ��������������������Ҫ1000��Ͱ
  ���������10Ϊ��������λ�����ֽ⣬��ôȡֵ��Χ�����0~9��ֻ��Ҫ����10��Ͱ����Ӧ��������Ҫ��������
  һ��أ���RΪ�����ֽ⣬��ֻ��ҪR��Ͱ��
*
*/

//ʵ����λ�����Ļ�������
#define MAX_digit 4//ÿ��Ԫ�����Ĺؼ�����
#define Radix 10

//����һ��bucket
typedef struct Node* ptr_to_Node;
struct Node {
	int key;
	ptr_to_Node next;
};

//bucketͷ���
struct head_node {
	ptr_to_Node head;
	ptr_to_Node tail;
};

typedef struct head_node bucket[Radix];

//Լ����λD=1����λD<=MAX_digit
int get_digit(int e, int D)
{
	int i, d;
	for (i = 1; i <= D; i++) {
		d = e % Radix;
		e = e / Radix;
	}
	return d;
}

void LSD_radix_sort(int arr[], int n)
{
	int D, Di, i;
	bucket B;
	ptr_to_Node temp, p, List = NULL;

	for (i = 0; i < Radix; i++)//��ʼ��ÿ��ͰΪ������
		B[i].head = B[i].tail = NULL;

	for (i = 0; i < n; i++) {//��arr[]�������List
		temp = (ptr_to_Node)malloc(sizeof(struct Node));
		temp->key = arr[i];
		temp->next = List;
		List = temp;
	}

	//�����￪ʼ����
	for (D = 1; D <= MAX_digit; D++) {
		//�������
		p = List;
		while (p) {
			Di = get_digit(p->key, D);
			temp = p;//��List��ժ��
			p = p->next;
			temp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = temp;
			else {
				B[Di].tail->next = temp;
				B[Di].tail = temp;
			}
		}

		//�ռ�����
		List = NULL;
		for (Di = Radix - 1; Di >= 0; Di--) {
			if (B[Di].head) {
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL;//���Ͱ
			}
		}
	}

	for (i = 0; i < n; i++) {//��List�Ż�arr[]���ͷſռ�
		temp = List;
		List = List->next;
		arr[i] = temp->key;
		free(temp);
	}
}
