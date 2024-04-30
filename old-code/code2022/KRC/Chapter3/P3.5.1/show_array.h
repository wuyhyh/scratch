#ifndef K_SHOW_ARRAY_H

#include <stdio.h>
void show(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
		if ((i + 1) % 10 == 0)
			putchar('\n');
	}
}

#define K_SHOW_ARRAY_H

#endif //K_SHOW_ARRAY_H
