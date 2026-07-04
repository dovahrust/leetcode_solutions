int minimumSwaps(int* nums, int len)
{
    if (nums == NULL || len <= 0) { return 0; }
    int cnt = 0;
    int lo = 0;
    int hi = len - 1;

    while (true) {
        while (lo < hi && nums[hi] == 0) {
            hi -= 1;
        }

        while (lo < hi && nums[lo] != 0) {
            lo += 1;
        }

        if (lo >= hi) {
            break;
        }

        cnt += 1;
        lo += 1;
        hi -= 1;
    }

    return cnt;
}
