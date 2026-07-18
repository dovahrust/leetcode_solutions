int compareBitonicSums(const int* nums, const int len)
{
    assert(len >= 3);
    int lo = 0;
    int hi = len - 1;
    int64_t sum_l = 0;
    int64_t sum_r = 0;

    while (lo < hi && nums[hi - 1] >= nums[hi]) {
        sum_r += nums[hi];
        hi -= 1;
    }

    if (hi == 0 || hi == len - 1) {
        fprintf(stderr, "invalid input, arr is not bitonic");
        exit(1);
    }

    while (lo < hi && nums[lo] <= nums[lo + 1]) {
        sum_l += nums[lo];
        lo += 1;
    }

    if (lo != hi) {
        fprintf(stderr, "invalid input, arr is not bitonic");
        exit(1);
    }

    if (sum_r < sum_l) {
        return 0;
    }

    if (sum_r > sum_l) {
        return 1;
    }

    return -1;
}
