constexpr int mod = 1'000'000'007;

static int dfs(const int n, const int k, const int target, span<int> memo, const size_t memo_cols) {
    if (target < 0 || n < 0) {
        return 0;
    }
    if (n == 0) {
        return target == 0 ? 1 : 0;
    }

    const size_t memo_idx = static_cast<size_t>(n) * memo_cols + static_cast<size_t>(target);
    if (memo[memo_idx] != - 1) {
        return memo[memo_idx];
    }

    int res = 0;
    for (int i = 1; i <= k; i += 1) {
        res = (res + dfs(n - 1, k, target - i, memo, memo_cols)) % mod;
    }

    memo[memo_idx] = res;
    return res;
}

class Solution {
public:
    static int numRollsToTarget(const int n, const int k, const int target) {
        assert(n >= 1 && n <= 30 && k >= 1 && k <= 30 && target >= 1 && target <= 1000);
        const size_t memo_cols = target + 1;
        const size_t memo_len = static_cast<size_t>(n + 1) * memo_cols;
        auto memo = vector<int>(memo_len, -1);

        return dfs(n, k, target, memo, memo_cols);
    }
};
