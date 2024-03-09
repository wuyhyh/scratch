#include<stdio.h>
#include<time.h>

#define N 3500

void print_n1(int n)
{
	for (int i = 1; i <= n; i++)
		printf("%d ", i);
}

void print_n2(int n)
{
	if (n > 0)
		print_n2(n - 1);
	printf("%d ", n);
}

int main()
{
	clock_t start, end;

	start = clock();
	print_n2(N);
	end = clock();
	printf("\n%f\n", (double)(end - start) / CLOCKS_PER_SEC);

	clock_t start1, end1;

	start1 = clock();
	print_n1(N);
	end1 = clock();
	printf("\n%f\n", (double)(end1 - start1) / CLOCKS_PER_SEC);

	return 0;
}

//解决问题的效率和空间利用效率有关系