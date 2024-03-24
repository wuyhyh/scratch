import sys
import keyword


# print(keyword.kwlist)
# print(type(keyword.kwlist))


def print_keywords():  # 输出python的关键字
    for i in range(0, len(keyword.kwlist)):
        print(i + 1, " : ", keyword.kwlist[i])


if __name__ == '__main__':
    print("main")
    print(sys.version)
    print(sys.path)
    print_keywords()

    n = None
    print(n)
    for i in range(6):
        print(i)

    for i in range(10, 6, -1):
        print(i)
    print(type(range))

    print(5 / 2)
    print(5 // 2)  # round down
    print(-5 / 2)
    print(-5 // 2)
    print(int(-5 / 2))  # round to zero
    print(int(-5 // 2))

import math

print(math.pow(2, 100) < float("inf"))
print(float("-inf"))

arr = [1, 2, 3]
print(arr)
arr.append(4)
arr.append(5)
print(arr)
arr.pop()
print(arr)
arr.insert(2, 22)
print(arr)
arr.remove(2)
print(arr)

m = 12
arr = [7] * m
print(arr)
print(len(arr))

nums = [12, 45, 74, 78]
for i in range(len(nums)):
    print(nums[i])

for n in nums:
    print(n)

for i, n in enumerate(nums):
    print(i, n)

nums1 = [2, 3, 4]
nums2 = [3, 4, 5]
for n1, n2 in zip(nums1, nums2):
    print(n1, n2)

nums1.reverse()
print(nums1)
print(nums2)

# list comprehension
arr = [i for i in range(5)]
print(arr)

arr = [i + 3 for i in range(4)]
print(arr)

arr.sort(reverse=True)
print(arr)

arr = ['wyh', 'wuyh', 'wuyuhang']
arr.sort(key=lambda x: len(x))
print(arr)

# 2d list
arr = [[0] * 4 for i in range(4)]
print(arr)

str = "abc"
print(str)
print(str[0:2])
print(str[-1])

# ASCII
print(ord('a'))

# combine strings
strings = ["abc", "def", "ghl"]
print("***".join(strings))
print("".join(strings))
print(" ".join(strings))

# 双端队列
from collections import deque

queue = deque()
queue.append(1)
queue.append(32)
print(queue)

queue.appendleft(67)
print(queue)
queue.popleft()
print(queue)

queue.pop()
print(queue)

# hash set
mset: set[int] = set()
mset.add(1)
mset.add(34)
print(mset)

print(2 in mset)
print(1 in mset)

print(len(mset))
mset.remove(1)
print(mset)

mset = {i for i in range(9)}
print(mset)

# hashmap
hmap = {}
hmap["alice"] = 88
hmap["bob"] = 11
print(hmap)
for key in hmap:
    print(key, hmap[key])

for val in hmap.values():
    print(val)

for key, val in hmap.items():
    print(key, val)

print("alice" in hmap)
hmap.pop("alice")
print("alice" in hmap)
print(hmap)
hmap["bob"] = 100
print(hmap)

name_map = {"suhuiqing": 2000, "linchuting": 1998}
print(name_map)

# 解决图问题
imap = {i: 2 * i for i in range(10)}
print(imap)

# tuples:我觉得这种数据类型就像是n维空间中的点
hsmap = {(1, 2): "point1"}
print(hsmap[(1, 2)])

# heaps
import heapq

minHeap = []
heapq.heappush(minHeap, 13)
heapq.heappush(minHeap, 423)
heapq.heappush(minHeap, 24)

print(minHeap)
print(minHeap[0])

while len(minHeap):
    print(heapq.heappop(minHeap))

# 只有小顶堆，要用大顶堆的话实现（*-1）
arr = [-2, -1, -4, -58]
for i in arr:
    i = -i
heapq.heapify(arr)
while arr:
    print(-1 * heapq.heappop(arr))


# function
def outer(a, b):
    c = "c"

    def inner():  # 内层函数继承外层函数的变量
        return " ".join(a + b + c)

    return inner()


print(outer("a", "b"))


# 这个函数的行为为啥我看不懂呢
def double(arr, val):
    def helper():
        for i, n in enumerate(arr):
            arr[i] *= 2

        nonlocal val
        val *= 2

    helper()
    print(arr, val)


nums = [1, 2]
val = 3
double(nums, val)
print(nums)
print(val)

print("**********")


# class:
class myclass:
    def __init__(self, nums):
        self.nums = nums
        self.size = len(nums)

    def get_length(self):
        return self.size

    def get_double_length(self):
        return 2 * self.get_length()


x = myclass([42, 23])
print(x.get_length())


class Wuyh:
    def __init__(self, value):
        self.value = value

    def display(self):
        print(self.value)


y = Wuyh(27)
y.display()
