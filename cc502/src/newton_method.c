#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static double improve(double guess, double x)
{
	return (x / guess + guess) / 2;
}

double abs_d(double a)
{
	return (a > 0) ? a : -a;
}

static bool good_enough(double guess, double x)
{
	double delta = guess * guess - x;
	if (abs_d(delta) < 0.000001)
		return true;
	return false;
}

static double sqr_iter(double guess, double x)
{
	if (good_enough(guess, x))
		return guess;
	return sqr_iter(improve(guess, x), x);
}

double sqr(int num)
{
	double input = (double)num;
	return sqr_iter(1.0, input);
}

int main(int argc, char *argv[])
{
	int input = atoi(argv[1]);
	printf("Root of %d is %.5f\n", input, sqr(input));

	return 0;
}
