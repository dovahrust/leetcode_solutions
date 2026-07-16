static inline int gcd_int(int a, int b)
{
    assert(a >= 0 && b >= 0);
    while (b != 0) {
        const int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(int*)a_ptr;
    const int b = *(int*)b_ptr;
    return (a > b) - (a < b);
}

long long gcdSum(int* nums, const int len)
{
    assert(len > 0);
    int max = 0;

    for (int i = 0; i < len; i += 1) {
        max = max_int(max, nums[i]);
        nums[i] = gcd_int(max, nums[i]);
    }

    qsort(nums, (size_t)len, sizeof(*nums), cmp);

    int lo = 0;
    int hi = len - 1;
    long long sum = 0;

    while (lo < hi) {
        sum += gcd_int(nums[lo], nums[hi]);
        lo += 1;
        hi -= 1;
    }

    return sum;
}
