typedef ptrdiff_t isize;

class Solution {
public:
    static bool canCross(const span<const int> stones) {
        assert(std::ssize(stones) >= 2 && std::ssize(stones) <= 2000 && stones[0] == 0);
        const int len = std::ssize(stones);
        for (int i = 1; i < len; i += 1) {
            assert(stones[i] > stones[i - 1]);
            const int diff_adj = stones[i] - stones[i - 1];
            if (diff_adj > i) {
                return false;
            }
        }

        const int dp_cols = len + 1;
        auto dp = vector<int8_t>(len * dp_cols, 0);
        dp[0] = 1;

        for (int i = 1; i < len; i += 1) {
            const int curr = stones[i];
            const int curr_base = i * dp_cols;
            for (int j = i; j >= 0; j -= 1) {
                const int prev = stones[j];
                const int prev_base = j * dp_cols;
                const int diff = curr - prev;

                if (diff > i) {
                    break;
                }

                if (dp[prev_base + diff - 1] || dp[prev_base + diff] || dp[prev_base + diff + 1]) {
                    if (i == len - 1) {
                        return true;
                    }

                    dp[curr_base + diff] = 1;
                }
            }
        }

        return false;
    }
};
