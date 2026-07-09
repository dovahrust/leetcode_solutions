static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* pathExistenceQueries(const int n, const int* nums, const int len, const int max_diff, 
                           int** queries, const int queries_len, const int* queries_col_len, int* return_len)
{
    assert(len > 0 && nums != NULL && return_len != NULL &&
           queries_len > 0 && queries_col_len != NULL && queries != NULL);

    *return_len = queries_len;
    int* ranks = malloc((size_t)len * sizeof(*ranks));
    assert(ranks != NULL);
    ranks[0] = 0;
    for (int i = 1; i < len; i += 1) {
        assert(nums[i] >= nums[i - 1]);
        if (nums[i] - nums[i - 1] <= max_diff) {
            ranks[i] = ranks[i - 1];
        } else {
            ranks[i] = ranks[i - 1] + 1;
        }
    }

    bool* res =  malloc((size_t)queries_len * sizeof(*res));
    assert(res != NULL);

    for (int i = 0; i < queries_len; i += 1) {
        const int* q = queries[i];
        assert(q != NULL && queries_col_len[i] == 2);
        const int lo = min_int(q[0], q[1]);
        const int hi = max_int(q[0], q[1]);
        assert(lo >= 0 && hi >=0 && lo < len && hi < len);
        res[i] = (ranks[lo] == ranks[hi]);
    }

/* cleanup: */
    free(ranks);
    return res;
}
