//
// Created by root on 4/17/24.
//

#include <stdio.h>

void farewell(char *someone)
{
	printf("*****************************\n");
	fprintf(stdout, "\t再见了，%s！\n", someone);
	printf("*****************************\n");
}

int main(int argc, char *argv[])
{
	char *grandpa_name = "爷爷";
	farewell(grandpa_name);
	return 0;
}