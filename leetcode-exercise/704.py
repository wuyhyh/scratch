# 使用Python作为解决算法问题的语言是不错的

# 二分查找的简单实现

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        i, j = 0, len(nums) - 1;
        while i <= j:
            m = (i + j) // 2
            if nums[m] < target:
                i = m + 1
            elif nums[m] > target:
                j = m - 1
            else:
                return m
        return -1
