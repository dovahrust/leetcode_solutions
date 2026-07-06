class Solution:
    def minCostToMoveChips(self, position: List[int]) -> int:
        cnt = [0] * 2

        for p in position:
            cnt[(p & 1)] += 1

        return min(cnt)
