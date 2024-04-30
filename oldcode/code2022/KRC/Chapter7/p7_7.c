#include <stdio.h>
#include <string.h>

int getline_w(char *line, int max)
{
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

int main()
{
	char nline[30];
	getline_w(nline, 100);
	printf("%s\n", nline);

	return 0;
}
