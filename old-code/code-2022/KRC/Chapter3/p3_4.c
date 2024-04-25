#include <stdio.h>

int main()
{
	int c;
	int nwhite = 0;
	int nother = 0;
	int ndigits[10] = { 0 };

	while ((c = getchar()) != EOF) {
		switch (c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			ndigits[c - '0']++;
			break;
		case ' ':
		case '\n':
		case '\t':
			nwhite++;
			break;
		default:
			nother++;
			break;
		}
	}

	printf("nwhite = %d\tnother = %d\n", nwhite, nother);
	for (int i = 0; i < 10; i++) {
		printf("%d ", ndigits[i]);
	}
	putchar('\n');
	return 0;
}
