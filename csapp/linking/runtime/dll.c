/******************************************************************************
 *
 * Name: dll.c - Description
 * Created on 2024/05/05
 * Copyright (C) 2022 - 2024, wyh.
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = { 1, 2 };
int y[2] = { 3, 4 };
int z[2];

int main()
{
	void *handle;
	void (*addvec)(int *, int *, int *, int);
	char *error;

	/*dynamically load the shared library that contains addvec() */
	handle = dlopen("./libvector.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	return 0;
}
