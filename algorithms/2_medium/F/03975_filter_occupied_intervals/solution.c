static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

struct vec {
    int** ptr;
    size_t len;
    size_t cap;
};

static inline void vec_push(struct vec* res, int* val)
{
    if (res->len == res->cap) {
        const size_t new_cap = res->cap == 0 ? 4 : 2 * res->cap;
        res->ptr = realloc(res->ptr, new_cap * sizeof(*res->ptr));
        assert(res->ptr != NULL);
        res->cap = new_cap;
    }
    res->ptr[res->len] = val;
    res->len += 1;
}

static inline void insert_to_res(struct vec* res, const int lo, const int hi,
                                const int free_start, const int free_end
) {
    if (hi < free_start || lo > free_end) {
        int* temp = malloc(2 * sizeof(*temp));
        assert(temp != NULL);
        temp[0] = lo;
        temp[1] = hi;
        vec_push(res, temp);
    } else {
        if (lo < free_start) {
            int* temp = malloc(2 * sizeof(*temp));
            assert(temp != NULL);
            temp[0] = lo;
            temp[1] = free_start - 1;
            vec_push(res, temp);
        }

        if (hi > free_end) {
            int* temp = malloc(2 * sizeof(*temp));
            assert(temp != NULL);
            temp[0] = free_end + 1;
            temp[1] = hi;
            vec_push(res, temp);
        }
    }
}

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int* a = *(const int**)a_ptr;
    const int* b = *(const int**)b_ptr;
    return (a[0] > b[0]) - (a[0] < b[0]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** filterOccupiedIntervals(int** occupied_intervals, int len, int* cols,
                              int free_start, int free_end, int* return_len, int** return_cols_len)
{
    assert(len > 0 && occupied_intervals != NULL && return_len != NULL && return_cols_len != NULL);

    qsort(occupied_intervals, (size_t)len, sizeof(*occupied_intervals), cmp); 

    int lo = occupied_intervals[0][0];
    int hi = occupied_intervals[0][1];
    struct vec res = { ptr: NULL, len: 0, cap: 0};

    for (int i = 0; i < len; i += 1) {
        const int* o = occupied_intervals[i];
        if (o[0] <= hi + 1) {
            hi = max_int(hi, o[1]);
        } else {
            insert_to_res(&res, lo, hi, free_start, free_end);
            lo = o[0];
            hi = o[1];
        }
    }

    insert_to_res(&res, lo, hi, free_start, free_end);

    *return_len = (int)res.len;
    if (res.len == 0) {
        return NULL;
    }
    int* res_cols_len = malloc(res.len * sizeof(*res_cols_len));
    assert(res_cols_len != NULL);
    for (size_t i = 0; i < res.len; i += 1) {
        res_cols_len[i] = 2;
    }
    *return_cols_len = res_cols_len;

    return res.ptr;
}
