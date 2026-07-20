/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

static inline int calc_pow_2(int n)
{
    int res = 0;
    while (n > 0) {
        res += 1;
        n /= 2;
    }
    return res;
}

int* pathInZigZagTree(const int label, int* return_len)
{
    assert(label >= 1 && return_len != NULL);
    const int pow_2 = calc_pow_2(label);
    int* res = malloc((size_t)pow_2 * sizeof(*res));
    assert(res != NULL);
    *return_len = pow_2;
    int curr_val = label;
    int hi = (1 << pow_2) - 1;
    int lo = 1 << (pow_2 - 1);

    for (int i = pow_2 - 1; i >= 0; i -= 1) {
        res[i] = curr_val;

        curr_val = (hi + lo - curr_val) / 2;
        hi /= 2;
        lo /=2;
    }

    return res;
}
