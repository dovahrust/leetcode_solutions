typedef ptrdiff_t isize;

static inline int min_isize(const isize a, const isize b)
{
    return a < b ? a : b;
}

int minCostToMoveChips(int* position, int position_len)
{
    const isize len = position_len;
    isize cnt[2] = { 0 };

    for (isize i = 0; i < len; i += 1) {
        cnt[(position[i] & 1)] += 1;
    }

    const isize res = min_isize(cnt[0], cnt[1]);
    assert(res <= INT_MAX);
    return (int)res;
}
