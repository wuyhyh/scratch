#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500
char *lineptr[MAXLINE]; //这是一个指针数组

#define MAXLEN 1000
int getline(char *line,
			int maxline) //getline函数将字符读入存放在line[]之中，返回行中字符数
{
	int c;
	int i;
	//不超出限制且未到结束处就不挺读入
	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i++] = c;
	}
	line[i] = '\0'; //加入结束符
	return i;
}

char *alloc(int n)
{
	char *temp = (char *)malloc(n * sizeof(*temp));
	return temp;
}

int readlines(char *lineptr[], int maxlines)
{
	int len;
	int nlines = 0;
	char *p;
	char line[MAXLEN];

	while ((len = getline(line, MAXLEN)) > 0) {
		if ((nlines > maxlines) || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

void writeline(char *lineptr[], int nline)
{
	for (int i = 0; i < nline; i++) {
		printf("%s\n", lineptr[i]);
	}
}

void writeline1(char *lineptr[], int nline)
{
	while (nline-- > 0)
		printf("%s\n", *lineptr++); //lineptr是一个数组名，可以这样写
}

void swap(char *arr[], int i, int j)
{
	char *temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void q_sort(char *lineptr[], int left, int right)
{
	int i;
	int last;
	int partition = (right + left) / 2;

	if (left >= right)
		return;

	swap(lineptr, partition, left);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (strcmp(lineptr[i], lineptr[left]) < 0) { //last是慢指针，i是快指针
			last++; //如果i处的元素大于切分元素，i就快速突进
			swap(
				lineptr, i,
				last); //如果i处的元素小于切分元素，那么就可以通知last移动腾出一个交换位置
		}
	}

	swap(lineptr, left,
		 last); //last标记了切分元素的最终位置，其左侧元素都小于切分元素
	q_sort(lineptr, left, last - 1);
	q_sort(lineptr, last + 1, right);
}

/*
int main()
{
	int nlines = 0;
	if ((nlines = readlines(lineptr, MAXLINE) > 0)) {
		q_sort(lineptr, 0, nlines - 1);
		writeline(lineptr, nlines);
		return 0;
	}
	else {
		printf("input too  big to sort\n");
		return -1;
	}
}
*/

int main()
{
	int nlines = 0;
	printf("%d\n", (nlines = readlines(lineptr, MAXLINE)));
	q_sort(lineptr, 0, nlines - 1);
	writeline(lineptr, MAXLINE);

	return 0;
}