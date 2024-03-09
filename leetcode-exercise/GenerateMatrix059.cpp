//
// Created by wyh on 2023/9/27.
//

#include <vector>
using namespace std;

class Solution {
public:
	vector<vector<int> > generateMatrix(int n)
	{
		vector<vector<int> > ret(n, vector<int>(n, 0)); // 定义一个n阶的矩阵
		int startx = 0;
		int starty = 0;
		int loop = n / 2;
		int mid = n / 2;
		int count = 1;
		int offset = 1;
		int i, j;
		while (loop--) {
			i = startx;
			j = starty;

			for (j = starty; j < starty + n - offset; ++j) {
				ret[startx][j] = count++;
			}
			for (i = startx; i < startx + n - offset; ++i) {
				ret[i][j] = count++;
			}
			for (; j > starty; j--) {
				ret[i][j] = count++;
			}
			for (; i > startx; i--) {
				ret[i][j] = count++;
			}

			startx++;
			starty++;
			offset += 2;
		}
		if (n % 2) {
			ret[mid][mid] = count;
		}
		return ret;
	}
};