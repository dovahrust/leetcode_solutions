class Solution:
    def countValidSubarrays(self, nums: list[int], x: int) -> int:
        assert(x >= 1 and x <= 9)
        n = len(nums)
        cnt = 0

        for i in range(n):
            s = 0
            for j in range(i, n):
                s += nums[j]
                lowest_dig = s % 10
                if lowest_dig == x:
                    temp = s
                    while temp >= 10:
                        temp //= 10
                    highest_dig = temp
                    if highest_dig == x:
                        cnt += 1

        return cnt
