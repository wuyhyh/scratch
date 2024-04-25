//
// Created by wyh on 2023/9/26.
//
#include <vector>
using namespace std;

class Solution {
public:
	/*
	 * 使用滑动窗口来实现寻找最小子数组的问题
	 * 窗口中的元素、窗口的左边界和右边界
	 * */
	int minSubArrayLen(int s, vector<int> &nums)
	{
		int result = INT32_MAX;
		int sum = 0;
		int i = 0; // 慢指针
		int j; // 快指针
		int subLength = 0;
		for (j = 0; j < nums.size(); ++j) {
			sum += nums[j];
			while (sum >= s) { // 这里是改变窗口的条件
				subLength = j - i + 1; //窗口的长度，也就是子数组的长度
				result = (result < subLength) ? result : subLength;
				sum -=
					nums[i++]; // 左边的指针在改变了长度之后，sum的值要发生变化
			}
		}
		return (result == INT32_MAX) ? 0 : result;
	}
};
