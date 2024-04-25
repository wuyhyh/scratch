#include<stdio.h>

void move(int n, int start, int goal, int temp)
{
	if (n == 1)
		return;
	else {
		move(n - 1, start, temp, goal);
		printf("move disk %d form %d to %d\n", n, start, goal);
		move(n - 1, temp, goal, start);
	}		
}

void move1(int n, char from, char buffer, char to) 
{
	if (n == 1) {
		printf("Move %d form %c to %c\n", 1, from, to); 
	}
	else {
		move1(n - 1, from, to, buffer);
		move1(1, from, buffer, to);
		move1(n - 1, buffer, from, to);
	}
}


int main()
{
	move1(3, 'A','B','C');
	move(3, 1, 3, 2);

	return 0;
}