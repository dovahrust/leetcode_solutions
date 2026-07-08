typedef ptrdiff_t isize;

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(int*)a_ptr;
    const int b = *(int*)b_ptr;
    return (a > b) - (a < b);
}

static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

long long makeSimilar(int* nums, int nums_len, int* target, int target_len)
{
    assert(nums_len == target_len);
    const isize len = nums_len;
    qsort(nums, (size_t)len, sizeof(*nums), cmp);
    qsort(target, (size_t)len, sizeof(*target), cmp);

    isize idx_odd = 0;
    isize idx_even = 0;
    isize idx_target = 0;
    int64_t cnt = 0;

    while (true) {
        while (idx_odd < len && (nums[idx_odd] & 1) == 0) {
            idx_odd += 1;
        }
        while (idx_even < len && (nums[idx_even] & 1) == 1) {
            idx_even += 1;
        }

        if (idx_odd == len && idx_even == len) {
            break;
        }

        if ((target[idx_target] & 1) == 1) {
            assert(idx_odd < len && "invalid input: missing odd number");
            cnt += abs_int(target[idx_target] - nums[idx_odd]) / 2;
            idx_odd += 1;
        } else {
            assert(idx_even < len && "invalid input: missing even number");
            cnt += abs_int(target[idx_target] - nums[idx_even]) / 2;
            idx_even += 1;
        }
        idx_target += 1;
    }

    return cnt / 2;
}
