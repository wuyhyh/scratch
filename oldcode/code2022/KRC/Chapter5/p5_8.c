#include <stdio.h>

//这两种方式存储的东西是不一样的，但引用起来一样。

char *month_name(int n)
{
	static char *name[] = { "Illegal month", "January",	  "Febuary", "March",
							"Aprial",		 "May",		  "June",	 "July",
							"August",		 "September", "October", "November",
							"December" };
	return name[n];
}

char name[][16] = { "Illegal month", "January",	  "Febuary", "March",
					"Aprial",		 "May",		  "June",	 "July",
					"August",		 "September", "October", "November",
					"December" };

int main()
{
	printf("%s\n", month_name(12));
	printf("%s\n", name[12]);

	return 0;
}
