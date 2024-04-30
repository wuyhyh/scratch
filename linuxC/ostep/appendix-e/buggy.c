//
// Created on 4/18/24.
//

// gdb是强大的工具，慢慢积累用法

#include <stdio.h>

struct data {
	int x;
};

int main(int argc, char *argv[])
{
	struct data *p = NULL;
	printf("%d\n", p->x);
}