#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
	char *name;
	char *defn;
	struct nlist *next;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) //hash函数，通过for循环进行变换
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval; //hash函数
	}

	return hashval % HASHSIZE;
}

//lookup函数在表中查找，如果找到返回指向块的指针，否则返回NULL
struct nlist *lookup(char *str)
{
	struct nlist *np;
	for (np = hashtab[hash(str)]; np != NULL;
		 np = np->next) { //遍历链表的标准方法
		if (strcmp(str, np->name) == 0) {
			return np;
		}
	}

	return NULL;
}

char *str_dup(char *str) //把字符移动到一个安全的地方
{
	char *p = (char *)malloc(strlen(str) + 1);
	if (p != NULL) {
		strcpy(p, str);
	}
	return p;
}

//通过lookup函数判断名字是不是已经存在，如果存在就更新他的定义，否则创建一个新项
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { //没有找到
		np = (struct nlist *)malloc(sizeof(*np));
		if (np == NULL ||
			(np->name = str_dup(name)) == NULL) { //分配失败或者名字为空
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free((void *)np->defn);
	}
	if ((np->defn = str_dup(defn)) == NULL)
		return NULL;

	return np;
}

void print_tab(struct nlist *tab[], int n)
{
	for (int i = 0; i < n; i++) {
		//while (tab[i]->next !=NULL) {
		//	printf("%s = %s\n", tab[i++]->name, tab[i++]->defn);
		//}
		//printf("%s = %s\n", tab[i]->name, tab[i]->defn);
		printf("%s\n", tab[i]->name);
	}
}

int main()
{
	install("wuyuhang", "wu");
	install("jujiayi", "ju");
	print_tab(hashtab, HASHSIZE);

	return 0;
}
