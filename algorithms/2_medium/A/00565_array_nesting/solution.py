class Solution:
    def arrayNesting(self, nums: List[int]) -> int:
        n = len(nums)
        longest = 0

        for i in range(n):
            curr_idx = i
            count = 0
            while nums[curr_idx] >= 0:
                next_idx = nums[curr_idx]
                assert(next_idx < n)
                nums[curr_idx] = -nums[curr_idx] - 1
                count += 1
                curr_idx = next_idx
            longest = max(longest, count)

        for i in range(n):
            nums[i] = -nums[i] - 1

        return longest
