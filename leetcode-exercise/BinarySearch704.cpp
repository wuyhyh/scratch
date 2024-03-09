#include <vector>
using namespace std;

class Solution {
public:
	int search(vector<int> &nums, int target)
	{
		int left = 0;
		int right = nums.size() - 1; // 闭区间的右边界限是size() - 1
		while (left <= right) { // 这里使用小于等于符号，因为使用的是闭区间
			int middle = left + (right - left) / 2;
			if (nums[middle] > target) {
				right = middle - 1;
			} else if (nums[middle] < target) {
				left = middle + 1;
			} else {
				return middle;
			}
		}
		return -1;
	}
};

// 这是做的leetcode第一个题，我发现MacBook Pro还是不习惯，不是很好用，不过字体很漂亮