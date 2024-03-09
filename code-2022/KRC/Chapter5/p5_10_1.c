#include <stdio.h>
#include <string.h>

//这是一个模式查找程序，从命令行接受要查找的pattern
#define MAXLINE 1000

int getline(char *line, int lim)
{
	int i = 0;
	int c;

	while ((c = getchar()) != EOF && c != '\n' && i < lim) {
		line[i++] = c;
	}
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}

int main(int argc, char *argv[])
{
	char line[MAXLINE];

	while (getline(line, MAXLINE) > 0) {
		if (strstr(line, argv[1]) != NULL) {
			printf("%s\n", line);
		}
	}

	return 0;
}
