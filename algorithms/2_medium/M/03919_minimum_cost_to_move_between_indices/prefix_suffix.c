static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minCost(const int* nums, const int len, int** queries, const int queries_len,
             const int* queries_col_len, int* return_len)
{
    assert(len >= 2 && queries_len > 0 && nums != NULL && queries != NULL && queries_col_len != NULL &&
           queries_col_len[0] == 2 && return_len != NULL);
    int* buff = calloc(2 * (size_t)len, sizeof(*buff));
    assert(buff != NULL);
    int* prefix = &buff[0];
    int* suffix = &buff[len];
    int* res = malloc((size_t)queries_len * sizeof(*res));
    assert(res != NULL);
    *return_len = queries_len;

    prefix[1] = 1;
    for (int i = 1; i < len - 1; i += 1) {
        assert(nums[i - 1] < nums[i] && nums[i] < nums[i + 1]);
        const int diff_l = abs_int(nums[i] - nums[i - 1]);
        const int diff_r = abs_int(nums[i + 1] - nums[i]);

        if (diff_l > diff_r) {
            prefix[i + 1] = 1 + prefix[i];
        } else {
            prefix[i + 1] = diff_r + prefix[i];
        }
    }

    suffix[len - 2] = 1;
    for (int i = len - 2; i >= 1; i -= 1) {
        const int diff_l = abs_int(nums[i] - nums[i - 1]);
        const int diff_r = abs_int(nums[i + 1] - nums[i]);

        if (diff_l <= diff_r) {
            suffix[i - 1] = 1 + suffix[i];
        } else {
            suffix[i - 1] = diff_l + suffix[i];
        }
    }

    for (int i = 0; i < queries_len; i += 1) {
        const int l = queries[i][0];
        const int r = queries[i][1];
        assert(l >= 0 && r >= 0 && l < len && r < len);

        if (l <= r) {
            res[i] = prefix[r] - prefix[l];
        } else {
            res[i] = suffix[r] - suffix[l];
        }
    }

/* cleanup: */
    free(buff);
    return res;
}
