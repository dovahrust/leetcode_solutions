static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

bool isIdealPermutation(const int* nums, const int len)
{
    assert(len >= 1 && nums != NULL);
    for (int i = 0; i < len; i += 1) {
        if (abs_int(nums[i] - i) > 1) {
            return false;
        }
    }

    return true;
}
