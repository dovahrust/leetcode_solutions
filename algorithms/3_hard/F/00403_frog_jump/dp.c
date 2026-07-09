bool canCross(const int* stones, const int len)
{
    assert(len >= 2 && len <= 2000 && stones!= NULL && stones[0] == 0);
    for (int i = 1; i < len; i += 1) {
        assert(stones[i] > stones[i - 1]);
        const int diff_adj = stones[i] - stones[i - 1];
        if (diff_adj > i) {
            return false;
        }
    }

    const int dp_cols = len + 1;
    bool* dp = calloc((size_t)(len * dp_cols), sizeof(*dp));
    assert(dp != NULL);
    dp[0] = true;
    bool res = false;

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
                    res = true;
                    goto cleanup;
                }

                dp[curr_base + diff] = true;
            }
        }
    }

cleanup:
    free(dp);
    return res;
}
