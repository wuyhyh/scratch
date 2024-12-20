#ifndef K_WORD_H
#define K_WORD_H

int getch();
void ungetch(int c);
int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);

#define NKEY 32
static struct key {
	char *word;
	int count;
} keytab[NKEY] = { { "auto", 0 },     { "break", 0 },	 { "case", 0 },
		   { "char", 0 },     { "const", 0 },	 { "continue", 0 },
		   { "default", 0 },  { "do", 0 },	 { "double", 0 },
		   { "else", 0 },     { "enum", 0 },	 { "extern", 0 },
		   { "float", 0 },    { "for", 0 },	 { "goto", 0 },
		   { "if", 0 },	      { "int", 0 },	 { "long", 0 },
		   { "register", 0 }, { "return", 0 },	 { "short", 0 },
		   { "signed", 0 },   { "sizeof", 0 },	 { "static", 0 },
		   { "struct", 0 },   { "switch", 0 },	 { "typedef", 0 },
		   { "union", 0 },    { "unsigned", 0 }, { "void", 0 },
		   { "volatile", 0 }, { "while", 0 } };

#endif //K_WORD_H
