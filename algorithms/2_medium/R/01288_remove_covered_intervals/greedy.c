typedef ptrdiff_t isize;

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int* a = *(const int**)a_ptr;
    const int* b = *(const int**)b_ptr;

    if (a[0] < b[0]) {
        return -1;
    } else if (a[0] > b[0]) {
        return 1;
    } else if (a[1] < b[1]) {
        return 1;
    } else if (a[1] > b[1]) {
        return -1;
    } else {
        return 0;
    }
}

int removeCoveredIntervals(int** intervals, int intervals_len, int* intervals_col_len)
{
    assert(intervals_len > 0 && intervals != NULL && intervals_col_len != NULL && intervals_col_len[0] == 2);
    const isize len = intervals_len;
    qsort(intervals, (size_t)len, sizeof(*intervals), cmp);

    isize invalids_cnt = 0;
    isize prev_end = intervals[0][1];

    for (isize i = 1; i < len; i += 1) {
        if (intervals[i][1] <=  prev_end) {
            invalids_cnt += 1;
        } else {
            prev_end = intervals[i][1];
        }
    }

    return (int)(len - invalids_cnt);
}
