class Solution:
    def minimumSwaps(self, nums: list[int]) -> int:
        cnt = 0
        lo = 0
        hi = len(nums) - 1

        while True:
            while lo < hi and nums[hi] == 0:
                hi -= 1

            while lo < hi and nums[lo] != 0:
                lo += 1

            if lo >= hi:
                break

            cnt += 1
            lo += 1
            hi -= 1

        return cnt
