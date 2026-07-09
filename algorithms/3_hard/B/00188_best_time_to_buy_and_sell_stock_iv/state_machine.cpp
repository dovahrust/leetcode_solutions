typedef ptrdiff_t isize;

class Solution {
public:
    int maxProfit(const int k_i32, const vector<int>& prices) {
        const isize len = std::ssize(prices);
        if (k_i32 <= 0 || len == 0) { return 0; }
        const isize k = k_i32;
        auto buff = vector<int>(2 * (k + 1));
        auto dp = span<int>(&buff[0], k + 1);
        auto hold = span<int>(&buff[k + 1], k + 1);

        for (isize i = 0; i < k + 1; i += 1) {
            dp[i] = 0;
            hold[i] = numeric_limits<int>::min();
        }

        for (const int p : prices) {
            for (isize i = k; i > 0; i -= 1) {
                dp[i] = std::max(dp[i], hold[i] + p);
                hold[i] = std::max(hold[i], dp[i - 1] - p);
            }
        }

        return dp[k];
    }
};
