#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"Stack.h"
#include"Queue.h"
#include"tree.h"

//层序创建
#define Noinfo 0
Bintree create_Bintree()
{
	char data;
	Bintree BT, T;
	Queue Q = create_Queue(100);

	//创建根结点
	scanf("%c", &data);
	if (data == Noinfo) {
		return NULL;
	}
	else {
		BT = (Bintree)malloc(sizeof(struct Tnode));
		BT->data = data;
		BT->left = BT->right = NULL;
		add_Queue(Q, BT);
	}

	while (!is_empty_Queue(Q)) {
		T = delete_Queue(Q);

		scanf("%c", &data);
		if (data == Noinfo) {
			T->left = NULL;
		}
		else {
			T->left = (Bintree)malloc(sizeof(struct Tnode));
			T->left->data = data;
			T->left->left = T->left->right = NULL;
			add_Queue(Q, T->left);
		}

		scanf("%c", &data);
		if (data == Noinfo) {
			T->right = NULL;
		}
		else {
			T->right = (Bintree)malloc(sizeof(struct Tnode));
			T->right->data = data;
			T->right->left = T->right->right = NULL;
			add_Queue(Q, T->right);
		}
	}

	return BT;
}


