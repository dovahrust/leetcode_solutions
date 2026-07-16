bool isMiddleElementUnique(int* nums, const int len) {
    assert(nums != NULL && len > 0 && (len & 1) == 1);
    const int mid_idx = len / 2;
    const int mid_val = nums[mid_idx];

    for (int i = 0; i < mid_idx; i += 1) {
        if (nums[i] == mid_val || nums[i + mid_idx + 1] == mid_val) {
            return false;
        }
    }

    return true;
}
