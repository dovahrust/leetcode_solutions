#define MOD 1000000007

static inline int64_t max_i64(const int64_t a, const int64_t b)
{
    return a > b ? a : b;
}

int kConcatenationMaxSum(const int* arr, const int len, const int k)
{
    assert(k >= 1 && len > 0 && arr != NULL);
    int64_t max_sub = 0;
    int64_t curr = 0;
    for (int i = 0; i < len; i += 1) {
        curr += arr[i];
        max_sub = max_i64(max_sub, curr);
        if (curr < 0) {
            curr = 0;
        }
    }

    if (k == 1 || max_sub == 0) {
        return (int)(max_sub % MOD);
    }

    int64_t sum = 0;
    for (int i = 0; i < len; i += 1) {
        sum += arr[i];
    }
    sum = max_i64(sum, 0);

    int64_t max_l = 0;
    curr = 0;
    for (int i = 0; i < len; i += 1) {
        curr += arr[i];
        max_l = max_i64(max_l, curr);
    }

    int64_t max_r = 0;
    curr = 0;
    for (int i = len - 1; i >= 0; i -= 1) {
        curr += arr[i];
        max_r = max_i64(max_r, curr);
    }

    const int64_t res = max_i64(sum * (k - 2) + max_l + max_r, max_sub);
    return (int)(res % MOD);
}
