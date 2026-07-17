static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

int minOperations(int* nums, const int len)
{
    assert(nums != NULL && len > 0);
    if (len == 1) { return 0; }
    const int max_val = len - 1;
    const int min_val = 0;

    for (int i = 1; i < len; i += 1) {
        const int abs_diff = abs_int(nums[i] - nums[i - 1]);
        if (abs_diff != 1) {
            if ((nums[i - 1] == min_val && nums[i] == max_val) || (nums[i] == min_val && nums[i - 1] == max_val)) {
                continue;
            }
            return -1;
        }
    }

    int min_idx = 0;
    for (int i = 0; i < len; i += 1) {
        if (nums[i] == 0) {
            min_idx = i;
            break;
        }
    }

    const int next_idx = (min_idx + 1) % len;
    if (nums[next_idx] == 1) {
        const int with_rev_idx = (len - 1) - min_idx;
        // 1 rev to get ..1,0,n,..;
        // with_rev_idx shift to left to get 0,n,n-1,...,1;
        // 1 shift to left to get n, n-1,..,0;
        // 1 rev to get for 0,1,2,..n;
        const int cost_with_rev = 1 + with_rev_idx + 1 + 1;
        // just simple shift to left;
        const int direct = min_idx;
        return min_int(direct, cost_with_rev);
    }

    const int with_rev_idx = (len - 1) - min_idx;
    // 1 rev to get ..n,0,1,..;
    // with_rev_idx shift to left to get 0,1,2,..,n;
    const int cost_with_rev = with_rev_idx + 1;
    // min_idx shift to left to get 0,n,...;
    // 1 shift to left to get n,...,0;
    // 1 rev to get 0,..,n;
    const int direct = min_idx + 1 + 1;
    return min_int(direct, cost_with_rev);
}
