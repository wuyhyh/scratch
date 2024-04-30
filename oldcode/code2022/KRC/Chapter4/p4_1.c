#include <stdio.h>

int getline(char line[], int max)
{
	int c;
	int i = 0;

	while ((c = getchar()) != EOF && c != '\n' && --max > 0) { //读取字符
		line[i++] = c;
	}
	if (c == '\n') //判断结尾
		line[i++] = '\n';
	line[i] = '\0'; //添加结束符

	return i;
}

int strindex(char s[], char target[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) { //从s[0]开始比对
		j = i;
		k = 0;
		while (target[k] != '\0' && s[j++] == target[k++]) {
			//在模式没有结束前从s[i]开始比对
			;
		}
		if (k > 0 && target[k] == '\0')
			return i;
	}

	return -1;
}

#define MAXLINE 1000

int main()
{
	char *partten = "ould";
	char line[MAXLINE];
	int found = 0;

	while (getline(line, MAXLINE) > 0) {
		if (strindex(line, partten) > 0) {
			printf(line);
			found++;
		}
	}
	printf("\n%d\n", found);

	return 0;
}
