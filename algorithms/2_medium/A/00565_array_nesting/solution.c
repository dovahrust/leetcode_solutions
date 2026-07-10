static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int arrayNesting(int* nums, const int len)
{
    int longest = 0;

    for (int i = 0; i < len; i += 1) {
        int curr_idx = i;
        int count = 0;
        while (nums[curr_idx] >= 0) {
            const int next_idx = nums[curr_idx];
            assert(next_idx < len);
            nums[curr_idx] = -nums[curr_idx] - 1;
            count += 1;
            curr_idx = next_idx;
        }
        longest = max_int(longest, count);
    }

    for (int i = 0; i < len; i += 1) {
        nums[i] = -nums[i] - 1;
    }

    return longest;
}
