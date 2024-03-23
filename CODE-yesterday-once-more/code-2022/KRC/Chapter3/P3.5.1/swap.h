#ifndef K_SWAP_H

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#define K_SWAP_H

#endif //K_SWAP_H
