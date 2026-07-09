#define K 2

typedef ptrdiff_t isize;

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int maxProfit(const int* prices, const int len_i32)
{
    assert(len_i32 > 0 && prices != NULL);
    const isize len = len_i32;
    int dp[K + 1] = { 0 };
    int hold[K + 1];
    for (isize i = 0; i < K + 1; i += 1) { hold[i] = INT_MIN; }

    for (isize i = 0; i < len; i += 1) {
        const int p = prices[i];

        for (isize j = K; j > 0; j -= 1) {
            dp[j] = max_int(dp[j], hold[j] + p);
            hold[j] = max_int(hold[j], dp[j - 1] - p);
        }
    }

    return dp[K];
}
