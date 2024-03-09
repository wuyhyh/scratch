#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//树的结点
struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};
//这是一种递归声明，是合法的

//talloc()函数分配一个结点大小的空间make a tnode
struct tnode *t_alloc()
{
	return (struct tnode *)malloc(sizeof(struct tnode));
}

//str_dup()函数把一个字符串复制到一个安全的位置
char *str_dup(char *str)
{
	char *p = (char *)malloc(strlen(str) + 1);
	if (p != NULL)
		strcpy(p, str);
	return p;
}

void treeprint(struct tnode *t) //中序遍历
{
	if (t != NULL) {
		treeprint(t->left);
		printf("%4d %s\n", t->count, t->word);
		treeprint(t->right);
	}
}

struct tnode *addtree(struct tnode *p, char *word)
{
	int cond;

	if (p == NULL) { //一个新的结点来了
		p = t_alloc();
		p->word = str_dup(word);
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcmp(word, p->word)) == 0) { //旧结点
		p->count++;
	} else if (cond < 0) {
		p->left = addtree(p->left, word);
	} else {
		p->right = addtree(p->right, word);
	}

	return p;
}

#define BUFFSIZE 100
char *buff[BUFFSIZE];
int bufp = 0;

int getch()
{
	return (bufp > 0) ? buff[--bufp] : getchar();
}

void ungetch(int c)
{
	buff[bufp++] = c;
}

int getword(char *word, int lim)
{
	char *w = word;
	int c;

	//返回读入的字符
	while (isspace(c = getch()))
		;
	if (c != EOF) {
		*w++ = c;
	}
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	while (--lim > 0) {
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
		w++; //这里读入多个字符
	}
	*w = '\0';
	return word[0];
}

#define MAXWORD 100
int main()
{
	char word[MAXWORD];
	struct tnode *root = NULL;

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word);
		}
	}

	treeprint(root);

	return 0;
}

//树由结点组成
//每一个结点包含一个指向内容的指针、一个统计出现次数的计数值、一个指向左子树的指针，一个指向右子树的指针
//每一个结点都有0个或者1个或者2个子节点

//要查找一棵树中有没有想要的结点，可以从根节点开始，如果小于就向左子树查找，大于就向右子树查找，这个过程是递归的。
//如果搜寻方向上没有子树，那么就说明查找的对象不存在
