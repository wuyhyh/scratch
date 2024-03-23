//������������ڣ���������һ��ĵڼ��졣
//��֤���Ϊ4λ�������ںϷ���

#include <iostream>
using namespace std;

int day_table[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31 },
	{0,31,29,31,30,31,30,31,31,30,31,30,31 },
};

bool is_leap_year(int year)//��ס������жϹ�ʽ
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true;
	else
		return false;
}

int day_of_year(int year, int month, int day)
{
	int days = 0;
	if (is_leap_year(year)) {
		for (int i = 1; i < month; i++) {
			days += day_table[1][i];
		}
		return days + day;
	}
	else {
		for (int i = 1; i < month; i++) {
			days += day_table[0][i];
		}
		return days + day;
	}
}

int main() 
{
	int year, month, day;
	cin >> year >> month >> day;
	cout << day_of_year(year, month, day) << endl;

	return 0;
}
