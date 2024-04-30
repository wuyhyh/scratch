#include <stdio.h>
#include <string.h>

int main()
{
	char *str = "wuyuhang";
	printf("%s\n\n", str);
	char ss[20];
	sprintf(ss, "%s", str);
	printf("%s\n", ss);

	return 0;
}