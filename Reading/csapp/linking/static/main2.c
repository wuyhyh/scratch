/******************************************************************************
 *
 * Name: main2.c - Test static library
 * Created on 2024/05/05
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <stdio.h>
#include "vector.h"

int x[2] = { 1, 2 };
int y[2] = { 3, 4 };
int z[2];

int main()
{
	addvec(x, y, z, 2);
	printf("z = [%d %d]\n", z[0], z[1]);
	return 0;
}
