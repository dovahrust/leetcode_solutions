class Solution:
    def isIdealPermutation(self, nums: List[int]) -> bool:
        for (i, num) in enumerate(nums):
            if abs(nums[i] - i) > 1:
                return False

        return True
