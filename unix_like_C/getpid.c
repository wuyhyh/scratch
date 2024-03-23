//
// Created on 2024/3/23.
//

#include <stdio.h>
#include <unistd.h>

int main()
{
	fprintf(stdout, "process id is %d\n", getpid());
	return 0;
}
