#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100

typedef int elemtype;

typedef int position;
typedef struct Lnode* p_to_Lnode;
struct Lnode {
	elemtype data[MAXSIZE];
	int last;
};
typedef p_to_Lnode List;

List create_L()
{
	List L = (List)malloc(sizeof(struct Lnode));
	L->last = -1;
	return L;
}

//二分查找
position binary_search(List L, elemtype target)
{
	position left = 0;
	position right = L->last;

	while (left <= right)
	{
		position middle = left + (right - left) / 2;
		if (L->data[middle] > target) {
			right = middle - 1;
		}
		else if (L->data[middle] < target) {
			left = middle + 1;
		}
		else {
			return middle;
		}
	}
	
	return -1;//没找到
}
