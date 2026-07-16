static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(const int*)a_ptr;
    const int b = *(const int*)b_ptr;
    return (a > b) - (a < b);
}

long long maxSum(int* nums, const int len, const int k, int mul_i32)
{
    assert(len > 0 && k >= 1 && k <= len && mul_i32 >= 1);
    long long mul = mul_i32;
    qsort(nums, (size_t)len, sizeof(*nums), cmp);
    assert(nums[0] >= 1);
    long long sum = 0;

    for (int i = len - 1; i >= len - k; i -= 1) {
        if (mul > 0) {
            sum += mul * nums[i];
            mul -= 1;
        } else {
            sum += nums[i];
        }
    }

    return sum;
}
