/******************************************************************************
 *
 * Name: sum.c - Description
 * Created on 2024/05/05
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

int sum(int *a, int n)
{
	int i, s = 0;
	for (i = 0; i < n; ++i) {
		s += a[i];
	}
	return s;
}
