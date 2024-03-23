//
// Created by wyh on 2023/9/25.
//
#include <vector>
using namespace std;

class Solution {
public:
	int removeElement_1(vector<int> &nums, int val)
	{
		int size = nums.size();
		// 暴力解法：遍历数组，找到需要移除的元素就把后面的元素移动覆盖当前的元素
		for (int i = 0; i < size; i++) {
			if (nums[i] == val) {
				for (int j = i; j < size - 1; ++j) {
					nums[j] = nums[j + 1];
				}
				size--;
				i--; // i指向的元素已经是刚才的元素的后一个元素
			}
		}
		return size;
	}

	//双指针法可以把双重循环要做的事情转换成一个快指针的循环，慢指针作为满足两种条件的数组元素的分界点。
	int removeElement(vector<int> &nums, int val)
	{
		int slow = 0;
		for (int fast = 0; fast < nums.size(); ++fast) {
			if (nums[fast] != val) { // 不等于的时候，才能通过慢指针的划分
				nums[slow++] = nums[fast];
			}
		}
		return slow;
	}
};
