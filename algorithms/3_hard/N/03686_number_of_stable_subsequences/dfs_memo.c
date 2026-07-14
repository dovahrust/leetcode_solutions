 #define MOD 1000000007

static int dfs(const int* nums, const int len, const int idx, int cnt_odd, int cnt_even, int* memo)
{
    if (idx == len) {
        return 0;
    }

    int memo_idx = 0;

    if (cnt_odd == 0 && cnt_even == 0) {
        memo_idx = idx;
    } else if (cnt_odd == 0 && cnt_even == 1) {
        memo_idx = len + idx;
    } else if (cnt_odd == 0 && cnt_even == 2) {
        memo_idx = 2 * len + idx;
    } else if (cnt_odd == 1 && cnt_even == 0) {
        memo_idx = 3 * len + idx;
    } else if (cnt_odd == 2 && cnt_even == 0) {
        memo_idx = 4 * len + idx;
    } else {
        fprintf(stderr, "unreachable!");
        exit(1);
    }

    if (memo[memo_idx] != -1) {
        return memo[memo_idx];
    }

    const int64_t skip = dfs(nums, len, idx + 1, cnt_odd, cnt_even, memo) ;

    if ((nums[idx] & 1) == 1) {
        cnt_odd += 1;
        cnt_even = 0;
    } else {
        cnt_even += 1;
        cnt_odd = 0;
    }

    const int64_t keep = cnt_odd < 3 && cnt_even < 3 ? (1 + dfs(nums, len, idx + 1, cnt_odd, cnt_even, memo)) : 0;

    const int res = (int)((skip + keep) % MOD);
    memo[memo_idx] = res;
    return res;
}

int countStableSubsequences(const int* nums, const int len)
{
    assert(len > 0 && len <= 100000 && nums != NULL);
    const int memo_len = len * 5;
    int* memo = malloc((size_t)memo_len * sizeof(*memo));
    assert(memo != NULL);
    for (int i = 0; i < memo_len; i += 1) {
        memo[i] = -1;
    }

    const int res = dfs(nums, len, 0, 0, 0, memo);
/* cleanup: */
    free(memo);
    return res;
}
