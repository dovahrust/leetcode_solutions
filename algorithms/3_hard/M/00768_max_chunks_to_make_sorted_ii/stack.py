class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        stack = []
        max_val = -sys.maxsize -1
        for a in arr:
            max_val = max(max_val, a)
            while stack and stack[-1] > a:
                stack.pop()
            stack.append(max_val)

        return len(stack)
