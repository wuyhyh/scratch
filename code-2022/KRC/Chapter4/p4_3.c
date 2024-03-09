//使用逆波兰表达式进行计算
//主函数不需要直到栈的信息，我们只提供push和pop来访问栈就可以了，\
因此我们将栈作为一个外部变量

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 //操作数最多
#define NUMBER '0' //找到数的标志

#define MAXVAL 100 //栈的最大深度

//这两个变量要被push和pop共享，因此使用外部变量。
int sp = 0; //栈顶指针
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL) {
		val[sp] = f;
		sp++;
	} else {
		printf("stack is full.\n");
	}
}

double pop()
{
	if (sp > 0) {
		sp--;
		return val[sp];
	} else {
		printf("stack is empty.\n");
		return 0.0;
	}
}

//getop函数完成取下一个操作数或运算符的任务
//需要跳过空格和制表符，如果下一个字符不是数字或小数点则返回
//否则把这些数字和字符串收集起来，然后返回NUMBER

#include <ctype.h>

int getch();
void ungetch(int);

int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t') //跳过空白和制表
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.') //不是数字
		return c;

	i = 0;
	if (isdigit(c)) //收集整数部分
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') //收集小数部分
		while (isdigit(s[++i] = c = getch()))
			;

	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

//程序中的getch和ungetch函数的用处在于，我们在读入输入的时候不清楚\
是否读入了足够的输入,必须超前读入一些输入，如果读入了过多的输入要返回
//在读取到一个非数字的字符之前，我们是不知道是否完整的读取了数字的。

//getch函数用于读取下一个要输入的字符
//ungetch函数用于把多读取的字符放回到输入中

//缓冲区和下标变量是两个函数共享的，要使用外部变量
#define BUFFSIZE 100

char buff[BUFFSIZE]; //缓冲区也是一个栈
int bufp = 0;

int getch()
{
	return (bufp > 0) ? buff[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp > BUFFSIZE)
		printf("too many characters.\n");
	else
		buff[bufp++] = c;
}

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s) != EOF)) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0) {
				push(pop() / op2);
				break;
			} else {
				printf("error: /0\n");
			}
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error,unknown command.\n");
			break;
		}
	}

	return 0;
}
