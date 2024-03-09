#include <stdio.h>
#include <time.h>
#include "rand_int.h"
#include "sort.h"

void blank(int n)
{
	while (n >= 1) {
		putchar('\n');
		n--;
	}
}

#define MAX 30000
#define N 20000
#define GAP 100

int main()
{
	int *ss = rand_int(N, MAX);
	int ss1[N];
	int ss2[N];

	for (int i = 0; i < N; i++) {
		ss1[i] = ss[i];
		ss2[i] = ss[i];
	}
	//print_int(ss, N,GAP);
	//blank(5);

	clock_t start, end;
	clock_t start1, end1;
	clock_t start2, end2;

	start = clock();
	insertion_sort(ss, N);
	end = clock();

	start1 = clock();
	selection_sort(ss1, N);
	end1 = clock();

	start2 = clock();
	quick_sort(ss2, 0, N - 1);
	end2 = clock();

	double cost_insertion = (double)(end - start) / CLOCKS_PER_SEC;
	double cost_selection = (double)(end1 - start1) / CLOCKS_PER_SEC;
	double cost_quick = (double)(end2 - start2) / CLOCKS_PER_SEC;
	//print_int(ss, N, GAP);

	printf("insertion sort cost %f s\n", cost_insertion);
	printf("selection sort cost %f s\n", cost_selection);
	printf("quick sort cost %f s\n", cost_quick);

	return 0;
}
