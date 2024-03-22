//使用busy waiting实现一个spin lock
#define N 2
#define TRUE 1
#define FALSE 0

int turn;
int interested[N];

void enter_region(int process)
{
	int other = 1 - process;
	turn = process;
	interested[process] = TRUE;
	while (turn == process && interested[other] == TRUE)
		;
}

void leave_region(int process)
{
	interested[process] = FALSE;
}
