int findMin(const int* nums, const int len)
{
    assert(len > 0 && nums != NULL);
    int lo = 0;
    int hi = len - 1;

    while (lo < hi) {
        const int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[hi]) {
            hi = mid;
        } else if (nums[mid] == nums[hi]) {
            hi -= 1;
        } else {
            lo = mid + 1;
        }
    }

    return nums[lo];
}
