class Solution:
    def candy(self, ratings: List[int]) -> int:
        n = len(ratings)
        vec = [1] * n
        cnt = 0

        for i in range(1, n):
            if ratings[i - 1] < ratings[i]:
                vec[i] = vec[i - 1] + 1

        for i in range(n - 1, 0, -1):
            if ratings[i - 1] > ratings[i]:
                vec[i - 1] = max(vec[i - 1], vec[i] + 1)
            cnt += vec[i - 1]
        cnt += vec[n - 1]

        return cnt
