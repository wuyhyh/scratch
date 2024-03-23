# brute force


def brute_force(nums):
    max_sum = nums[0]

    for i in range(0, len(nums)):
        curr_sum = 0
        for j in range(i, len(nums)):
            curr_sum += nums[j]
            max_sum = max(curr_sum, max_sum)
    return max_sum


if __name__ == '__main__':
    nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    ret = brute_force(nums)
    print(ret)
