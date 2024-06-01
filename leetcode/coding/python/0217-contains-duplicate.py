'''
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        hashset = set()

        for n in nums:
            if n in hashset:
                return True
            hashset.add(n)
        return False
'''

# 使用set集合
class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:
        set1 = set(nums)
        return len(set1) != len(nums)
