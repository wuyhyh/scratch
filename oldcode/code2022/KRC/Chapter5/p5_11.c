#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 120
char* lineptr[MAXLINE];
#define MAXLEN 100

void swap(void* v[], int i, int j)
{
	void* temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void q_sort(void* v[], int left, int right, int (*comp)(void* i, void* j)) //这里需要一个返回值是int，有两个void类型指针的函数做参数
{
	int i;
	int partition = (right + left) / 2;

	if (left >= right)
		return;

	swap(v, left, partition);
	int last = left;
	for (i = left + 1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0) {//这里使用了comp指向的那个函数
			swap(v, ++last, i);
		}
	}

	swap(v, last, left);
	q_sort(v, left, last - 1,comp);//comp就是一个函数的地址
	q_sort(v, last + 1, right,comp);
}

//这里是两种比较标准
//int strcmp(char* str1,char* str2);
int numcmp(char* str1, char* str2)
{
	double v1 = atof(str1);
	double v2 = atof(str2);
	if (v1 < v2) {
		return -1;
	}
	else if (v1 > v2) {
		return 1;
	}
	else {
		return 0;
	}
}

int getline(char* line, int lim)
{
	int c;
	int i = 0;
	while ((c = getchar()) != EOF && c != '\n'&&i<lim-1) {
		line[i++] = c;
	}
	if (c == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return i;
}

int readlines(char* lineptr[], int maxline)
{
	char line[MAXLEN];
	char* temp;
	int len;
	int nline = 0;
	while ((len = getline(line, MAXLEN)) > 0&&nline<maxline-1) {
		if ((temp = (char*)malloc(len * sizeof(*temp))) != NULL) {//这里是必不可少，在这里分配存储空间
			line[len - 1] = '\0';//删除换行符
			strcpy(temp, line);//把数据放到存储空间中
			lineptr[nline++] = temp;//指定指针去访问存储的数据
		}
	}
	return nline;
}

void writelines(char* lineptr[], int nline)
{
	while (nline > 0) {
		printf("%s\n", lineptr[--nline]);
	}
}

int main()
{
	int nline = readlines(lineptr, MAXLINE);
	printf("%d\n\n\n", nline);
	//q_sort(lineptr, 0, nline-1 , numcmp);
	q_sort(lineptr, 0, nline-1 , strcmp);
	writelines(lineptr, nline);

	return 0;
}
