//表格的操作

#include<iostream>
using namespace std;

int main()
{
	int row, col;
	int swap_row1, swap_col1, swap_row2, swap_col2;
	int insert_row;
	int insert_col;
	int find_row, find_col;
	while (cin >> row >> col) {
		cin >> swap_row1 >> swap_col1 >> swap_row2 >> swap_col2;
		cin >> insert_row;
		cin >> insert_col;
		cin >> find_row >> find_col;

		if (row > 9 || col > 9)
			cout << -1 << endl;
		else
			cout << 0 << endl;

		if (swap_row1 >= 0 && swap_row1 < row && swap_row2 >= 0 && swap_row2 < row /
			swap_col1 >= 0 && swap_col1 < col && swap_col2 >= 0 && swap_col2 < col)
			cout << 0 << endl;
		else
			cout << -1 << endl;

		if (row < 9 && insert_row >= 0 && insert_row < row)
			cout << 0 << endl;
		else
			cout << -1 << endl;

		if (col < 9 && insert_col >= 0 && insert_col < col)
			cout << 0 << endl;
		else
			cout << -1 << endl;

		if (find_row >= 0 && find_row < row && find_col >= 0 && find_col < col)
			cout << 0 << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}


