
#ifndef K_RAND_NUMBER_H

#pragma once
#include <stdlib.h>

int *rand_n(int max, int n)
{
	int *temp = (int *)malloc(n * sizeof(*temp));
	for (int i = 0; i < n; i++) {
		temp[i] = rand() % max + 1;
	}
	return temp;
}

#define K_RAND_NUMBER_H

#endif //K_RAND_NUMBER_H
