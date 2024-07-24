/******************************************************************************
 *
 * Name: addvec.c - Description
 * Created on 2024/05/05
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/
#include "vector.h"

void addvec(int *x, int *y, int *z, int n)
{
	int i;
	for (int i = 0; i < n; ++i) {
		z[i] = x[i] + y[i];
	}
}
