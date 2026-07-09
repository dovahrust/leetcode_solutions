typedef ptrdiff_t isize;

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int maxProfit(const int k_i32, const int* prices, const int len_i32) {
    assert(len_i32 >= 0);
    if (k_i32 <= 0 || len_i32 == 0) { return 0; }
    assert(prices != NULL);
    const isize k = k_i32;
    const isize len = len_i32;
    int* buff = malloc((size_t)(2 * (k + 1)) * sizeof(*buff));
    assert(buff != NULL);
    int* dp = &buff[0];
    int* hold = &buff[k + 1];

    for (isize i = 0; i < k + 1; i += 1) {
        dp[i] = 0;
        hold[i] = INT_MIN;
    }

    for (isize i = 0; i < len; i += 1) {
        const int p = prices[i];

        for (isize j = k; j > 0; j -= 1) {
            dp[j] = max_int(dp[j], hold[j] + p);
            hold[j] = max_int(hold[j], dp[j - 1] - p);
        }
    }

    const int res = dp[k];
/* cleanup: */
    free(buff);
    return res;
}
