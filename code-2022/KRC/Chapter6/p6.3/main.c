#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "word.h"

#define MAXWORD 100

int main()
{
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEY)) >= 0)
				keytab[n].count++;
	}

	int i = 0;
	while (i < NKEY) {
		if (keytab[i].count >= 0)
			printf("%s = %d\n", keytab[i].word, keytab[i].count);
		i++;
	}

	return 0;
}
