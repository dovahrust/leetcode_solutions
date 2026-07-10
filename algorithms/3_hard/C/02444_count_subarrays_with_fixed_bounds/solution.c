static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

long long countSubarrays(const int* nums, const int len, const int min_k, const int max_k)
{
    assert(len >= 2 && nums != NULL);
    int64_t cnt = 0;
    int begin = 0;
    int min_idx = 0;
    int max_idx = 0;

    for (int i = 0; i < len; i += 1) {
        const int num = nums[i];

        if (num > max_k || num < min_k) {
            min_idx = i + 1;
            max_idx = i + 1;
            begin = i + 1;
        } else {
            if (nums[min_idx] >= num) {
                min_idx = i;
            }
            if (nums[max_idx] <= num) {
                max_idx = i;
            }

            if (nums[max_idx] == max_k && nums[min_idx] == min_k) {
                cnt += min_int(min_idx, max_idx) - begin + 1;
            }
        }
    }

    return cnt;
}
