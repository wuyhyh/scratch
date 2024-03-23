//���ö�ջ��׺���ʽ��ֵ
//����Լ�����ʽ��num��opr֮���ÿո�ָ�

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"stack.h"

#define MAXOP 100//��ı��ʽ����
#define INFINITY 1e9//����������

//typedef double elemtype;

typedef enum { num, opr, end }type;

type get_op(char* expr, int* start, char* str)//��start����ʼ������󣬷���str�У�������������
{
	int i = 0;

	while ((str[0] = expr[(*start)++]) == ' ')//�������ʽǰ�Ŀո�
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
				op2 = INFINITY;//�����⣬��עΪ�����ľ��Ǵ���
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
				printf("δ֪�����\n");
				op2 = INFINITY;
				break;
			}
			if (op2 >= INFINITY)
				break;
		}
	}
	if (op2 < INFINITY)
		if (!is_empty(S))
			op2 = pop(S);//������ڴ˴�
		else
			op2 = INFINITY;
	free(S);
	return op2;//����������
}



int main()
{
	//result = 16\
	2 9 6 3 / + 5 - * 4 +
	char expr[MAXOP];
	elemtype f;

	fgets(expr, MAXOP, stdin);//����������ȡ���ַ�������string��
	f = postfix_exp(expr);
	if (f < INFINITY)
		printf("%.4f\n", f);
	else
		printf("���ʽ����\n");

	return 0;
}