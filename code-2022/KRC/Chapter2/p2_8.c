//编写一个程序去除掉字符串中的某个字符

#include <stdio.h>

void squess(char s[], int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++) {
		if (s[i] != c)
			s[j++] = s[i];
	} //等价于s[j]=s[i]；\
		    j++； 每当出现一个不是c的字符的时候，就执行拷贝然后移动到下一个位置
	s[j] = '\0';
}

//这一个函数将连接两个字符串
void strcat(char s[], char t[])
{
	int i, j;
	i = 0;
	while (s[i] != '\0') {
		i++;
	} //找到s[]的结尾
	j = 0;
	while ((s[i++] = t[j++]) != '\0') { //复制t[]到s[]的后面
		;
	}
}

int main()
{
	char ss[100] = "Sheu";
	printf("%s\n", ss);
	squess(ss, 'u');
	printf("%s\n", ss);
	char tt[] = " is died";
	strcat(ss, tt);
	printf("%s\n", ss);

	return 0;
}
