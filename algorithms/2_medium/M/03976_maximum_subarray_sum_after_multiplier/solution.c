struct data {
    int64_t by;
    int64_t by_mul;
    int64_t by_div;
};

static inline int64_t max_int64(const int64_t a, const int64_t b)
{
    return a > b ? a : b;
}

static inline struct data* init_max(const int* nums, const int len, const int64_t k)
{
    struct data* max = malloc(((size_t)len + 1) * sizeof(*max));
    assert(max != NULL);
    max[len] = (struct data){ by: 0, by_mul: 0, by_div: 0};
    int64_t by = 0;
    int64_t by_mul = 0;
    int64_t by_div = 0;
    for (int i = len - 1; i >= 0; i -= 1) {
        const int64_t num = nums[i];
        by_mul = max_int64(0, max_int64(by_mul, by) + num * k);
        by_div = max_int64(0, max_int64(by_div, by) + num / k);
        by = max_int64(0, by + num);
        max[i] = (struct data){ by: by, by_mul: by_mul, by_div: by_div};
    }

    return max;
}

long long maxSubarraySum(const int* nums, const int len, const int k)
{
    assert(k >= 1);
    const struct data* max = init_max(nums, len, k);
    int64_t by_l = 0;
    int64_t by_mul_l = 0;
    int64_t by_div_l = 0;
    int64_t res = INT64_MIN;

    for (int i = 0; i < len; i += 1) {
        const int64_t num = nums[i];
        int64_t by_r = max[i + 1].by;
        int64_t by_mul_r = max[i + 1].by_mul;
        int64_t by_div_r = max[i + 1].by_div;
        by_mul_l = max_int64(0 ,by_mul_l) + num * k;
        by_div_l = max_int64(0, by_div_l) + num / k;
        by_l = max_int64(0, by_l) + num;

        res = max_int64(res, by_mul_l + by_r);
        res = max_int64(res, by_div_l + by_r);
        res = max_int64(res, by_l + by_mul_r);
        res = max_int64(res, by_l + by_div_r);
    }

/* cleanup */
    free(max);
    return res;
}
