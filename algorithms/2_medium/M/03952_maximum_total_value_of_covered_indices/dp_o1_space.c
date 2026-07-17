static inline int64_t max_int64(const int64_t a, const int64_t b)
{
    return a > b ? a : b;
}

long long maxTotal(const int* nums, const int len, const char* s) {
    assert(len > 0 && nums != NULL && s != NULL && (size_t)len == strlen(s));
    int64_t prev_prev = 0;
    int64_t prev = 0;
    if (s[0] == '1') {
        prev = nums[0];
    }

    for (int i = 1; i < len; i += 1) {
        if (s[i] == '1') {
            const int64_t curr = max_int64(prev_prev + nums[i - 1], prev + nums[i]);
            prev = max_int64(prev, prev_prev + nums[i - 1]);

            prev_prev = prev;
            prev = curr;
        } else {
            prev_prev = prev;
        }
    }

    return prev;
}
