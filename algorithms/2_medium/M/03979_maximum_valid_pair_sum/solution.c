static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int maxValidPairSum(const int* nums, const int len, const int k)
{
    assert(k > 0 && k < len && nums != NULL);

    int max_lo = INT_MIN;
    int res = INT_MIN;
    const int end = len - k;
    for (int i = 0; i < end; i += 1) {
        max_lo = max_int(max_lo, nums[i]);
        res = max_int(res, max_lo + nums[i + k]);
    }

    return res;
}
