#define MOD 1000000007

static int dfs(const int n, const int k, const int target, int* memo, const size_t memo_cols)
{
    if (target < 0 || n < 0) {
        return 0;
    }
    if (n == 0) {
        return target == 0 ? 1 : 0;
    }

    const size_t memo_idx = (size_t)n * memo_cols + (size_t)target;
    if (memo[memo_idx] != - 1) {
        return memo[memo_idx];
    }

    int res = 0;
    for (int i = 1; i <= k; i += 1) {
        res = (res + dfs(n - 1, k, target - i, memo, memo_cols)) % MOD;
    }

    memo[memo_idx] = res;
    return res;
}

int numRollsToTarget(const int n, const int k, const int target)
{
    assert(n >= 1 && n <= 30 && k >= 1 && k <= 30 && target >= 1 && target <= 1000);
    const size_t memo_cols = target + 1;
    const size_t memo_len = (size_t)(n + 1) * memo_cols;
    int* memo = malloc(memo_len * sizeof(*memo));
    assert(memo != NULL);
    for (size_t i = 0; i < memo_len; i += 1) { memo[i] = -1; }

    const int res = dfs(n, k, target, memo, memo_cols);

/* cleanup: */
    free(memo);
    return res;
}
