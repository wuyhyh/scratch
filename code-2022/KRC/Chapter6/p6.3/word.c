#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "word.h"

#define BUFFSIZE 100
static char *buff[BUFFSIZE];
int bufp = 0;

int getch()
{
	return (bufp > 0) ? buff[--bufp] : getchar();
}

void ungetch(int c)
{
	buff[bufp++] = c;
}

int getword(char *word, int lim)
{
	char *w = word;
	int c;

	while (isspace(c = getch())) //跳过空白
		; //do nothing
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++) {
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

int binsearch(char *word, struct key tab[], int n)
{
	int low = 0;
	int high = n - 1;
	int cond;

	while (low <= high) {
		int middle = low + (high - low) / 2;
		cond = strcmp(tab[middle].word, word);
		if (cond < 0) {
			low = middle + 1;
		} else if (cond > 0) {
			high = middle - 1;
		} else {
			return middle;
		}
	}
	return -1;
}