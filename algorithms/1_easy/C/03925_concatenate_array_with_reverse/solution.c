/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* concatWithReverse(const int* nums, const int len, int* return_len)
{
    assert(len > 0 && nums != NULL && len <= (INT_MAX / 2) && return_len != NULL);
    int* res = malloc((size_t)(2 * len) * sizeof(*res));
    assert(res != NULL);
    for (int i = 0; i < len; i += 1) {
        res[i] = nums[i];
        res[2 * len - 1 - i] = nums[i];
    }
    *return_len = 2 * len;
    return res;
}
