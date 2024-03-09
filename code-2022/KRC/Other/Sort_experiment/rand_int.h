#ifndef K_RAND_INT_H

#include<stdlib.h>
#include<stdio.h>

int* rand_int(int n, int max)
{
	int* temp = (int*)malloc(n * sizeof(*temp));
	for (int i = 0; i < n; i++) {
		temp[i] = rand() % max + 1;
	}
	return temp;
}

void print_int(int arr[], int n, int gap)
{
	for (int i = 0; i < n; i += gap) {
		printf("%d ", arr[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}
}


#define K_RAND_INT_H

#endif //K_RAND_INT_H
