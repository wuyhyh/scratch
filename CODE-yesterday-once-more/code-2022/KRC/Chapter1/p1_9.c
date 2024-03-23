//字符'\0'是空字符，它的值是0
//字符串数组以空字符作为结束标志

//我们编写一个程序来输出读入的文本行中最长的行
//程序框架是：\
while(还有未处理的行)\
	if(比当前最长行还要长)\
		保存这一行和他的长度\
输出最长的行

//我们需要先编写一个读入行的函数getline()\
它读入文本的下一行并返回长度，我们约定读到文件结束符EOF时返回0\
每行都应该至少包含一个字符，只有换行符'\n'的行长度为1

//为了保存最长的行，我们需要一个函数copy()把最长行复制到一个安全的位置

#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline)
{
	int c;
	int i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c; //依次读取行中的每个字符
	}
	if (c == '\n') { //判断已经到达结尾
		line[i] = '\n';
		i++;
	}
	line[i] = '\0'; //添加空字符完成字符数组的构造

	return i; //返回长度
}

void copy(char to[], char from[])
{
	int i = 0;
	while ((to[i] = from[i]) != '\0') //依次复制到文件结尾
		i++;
}

int main()
{
	int curr_len; //当前行的长度
	int max_len = 0; //已发现的最长行的长度
	char curr_line_input[MAXLINE];
	char longest_line[MAXLINE];

	while ((curr_len = getline(curr_line_input, MAXLINE)) > 0) {
		if (curr_len > max_len) {
			copy(longest_line, curr_line_input);
			max_len = curr_len;
		}
	}

	if (max_len > 0)
		printf("%s\n", longest_line);

	return 0;
}
