class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        last_seen = [-1] * 3
        cnt = 0

        for (i, ch) in enumerate(s):
            last_seen[ord(ch) - ord('a')] = i
            cnt += 1 + min(last_seen)

        return cnt
