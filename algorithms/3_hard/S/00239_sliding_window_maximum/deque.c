struct pair {
    int idx;
    int val;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(const int* nums, const int nums_len, const int k, int* return_len)
{
    assert(k > 0 && k <= nums_len && nums_len <= 100000);
    const int res_len = nums_len - k + 1;
    int* res = malloc((size_t)res_len * sizeof(*res));
    int res_idx = 0;
    assert(res != NULL);
    *return_len = res_len;
    struct pair* q = malloc((size_t)k * sizeof(*q));
    assert(q != NULL);
    const int q_cap = k;
    int q_head = 0;
    int q_len = 0;

    for (int i = 0; i < nums_len; i += 1) {
        const int num = nums[i];
        if (i >= k) {
            if (q_len > 0 && q[q_head].idx <= i - k) {
                q_len -= 1;
                q_head = (q_head + 1) % q_cap;
            }
        }

        while (q_len > 0 && q[(q_head + q_len - 1) % q_cap].val <= num) {
            q_len -= 1;
        }

        const int tail = (q_head + q_len) % q_cap;
        q[tail].idx = i;
        q[tail].val = num;
        q_len += 1;

        if (i >= k - 1) {
            res[res_idx] = q[q_head].val;
            res_idx += 1;
        }
    }

/* cleanup: */
    free(q);
    return res;
}
