typedef ptrdiff_t isize;

constexpr isize k = 2;

class Solution {
public:
    static int maxProfit(const vector<int>& prices) {
        const isize len = std::ssize(prices);
        int dp[k + 1] = { 0 };
        int hold[k + 1];
        for (isize i = 0; i < k + 1; i += 1) { hold[i] = numeric_limits<int>::min(); }

        for (const int p : prices) {
            for (isize i = k; i > 0; i -= 1) {
                dp[i] = std::max(dp[i], hold[i] + p);
                hold[i] = std::max(hold[i], dp[i - 1] - p);
            }
        }

        return dp[k];
    }
};
