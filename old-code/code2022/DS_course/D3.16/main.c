//利用堆栈后缀表达式求值
//我们约定表达式的num和opr之间用空格分隔

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"stack.h"

#define MAXOP 100//最长的表达式界限
#define INFINITY 1e9//代表正无穷

//typedef double elemtype;

typedef enum { num, opr, end }type;

type get_op(char* expr, int* start, char* str)//从start处开始读入对象，放入str中，返回他的类型
{
	int i = 0;

	while ((str[0] = expr[(*start)++]) == ' ')//跳过表达式前的空格
		;

	while (str[i] != ' ' && str[i] != '\0')
		str[++i] = expr[(*start)++];
	if (str[i] == '\0')
		(*start)--;
	str[i] == '\0';


	if (i == 0)
		return end;
	else if (isdigit(str[0]) || isdigit(str[1]))
		return num;
	else
		return opr;
}

elemtype postfix_exp(char* expr)
{
	Stack S;
	type t;
	elemtype op1, op2;
	char str[MAXOP];
	int start = 0;

	S = create_s(MAXOP);
	op1 = op2 = 0.0;
	while ((t = get_op(expr, &start, str)) != end) {
		if (t == num)
			push(S, atof(str));
		else {
			if (!is_empty(S))
				op2 = pop(S);
			else
				op2 = INFINITY;//错误检测，标注为无穷大的就是错误
			if (!is_empty(S))
				op1 = pop(S);
			else
				op2 = INFINITY;

			switch (str[0]) {
			case '+':push(S, op1 + op2); break;
			case'-':push(S, op1 - op2); break;
			case'*':push(S, op1 * op2); break;
			case'/': {
				if (op2 != 0.0) {
					push(S, op1 / op2);
				}
				else {
					printf("divide 0 error!\n");
					op2 = INFINITY;
				}
			}break;
			default:
				printf("未知运算符\n");
				op2 = INFINITY;
				break;
			}
			if (op2 >= INFINITY)
				break;
		}
	}
	if (op2 < INFINITY)
		if (!is_empty(S))
			op2 = pop(S);//结果放在此处
		else
			op2 = INFINITY;
	free(S);
	return op2;//返回运算结果
}



int main()
{
	//result = 16\
	2 9 6 3 / + 5 - * 4 +
	char expr[MAXOP];
	elemtype f;

	fgets(expr, MAXOP, stdin);//从输入流中取得字符串放入string中
	f = postfix_exp(expr);
	if (f < INFINITY)
		printf("%.4f\n", f);
	else
		printf("表达式错误\n");

	return 0;
}