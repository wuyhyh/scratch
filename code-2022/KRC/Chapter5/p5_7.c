//多维数组类似矩阵一样按行存储，实际上使用并不多
//行号是不重要的，可以省略

static int day_table[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

void days_to_date(int year, int days, int *month, int *day)
{
	int leap = 0;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		leap = 1;
	int mon = 1;
	while (days > day_table[leap][mon]) {
		days -= day_table[leap][mon++];
	}
	*month = mon;
	*day = days;
}

int date_to_days(int year, int month, int day)
{
	int leap = 0;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		leap = 1;
	while (month > 1) {
		day += day_table[leap][--month];
	}
	return day;
}

#include <stdio.h>

int main()
{
	int days;
	printf("%d\n", (days = date_to_days(2022, 6, 8)));

	int month;
	int day;
	days_to_date(2022, days, &month, &day);
	printf("%d/%d/%d\n", 2022, month, day);

	return 0;
}
