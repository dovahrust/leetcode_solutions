#define MAX_HI 1000000000

struct vec {
    int* ptr;
    size_t cap;
    size_t len;
};

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(const int*)a_ptr;
    const int b = *(const int*)b_ptr;
    return (a > b) - (a < b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* sequentialDigits(int lo, int hi, int* return_len)
{
    assert(lo >= 10 && lo <= hi && hi <= MAX_HI && return_len != NULL);
    struct vec res = { NULL, 0, 0 };

    for (int start_dig = 1; start_dig <= 9; start_dig += 1) {
        int num = 0;

        for (int dig = start_dig; dig <= 9; dig += 1) {
            num = num * 10 + dig;

            if (num > hi) {
                break;
            }

            if (num >= lo) {
                if (res.len == res.cap) {
                    const size_t new_cap = (res.cap == 0 ? 4 : 2 * res.cap);
                    res.ptr = realloc(res.ptr, new_cap * sizeof(*res.ptr));
                    assert(res.ptr != NULL);
                    res.cap = new_cap;
                }
                res.ptr[res.len] = num;
                res.len += 1;
            }
        }
    }

    assert(res.len <= (size_t)INT_MAX);
    *return_len = (int)res.len;
    if (res.len == 0) {
        return NULL;
    }
    qsort(res.ptr, res.len, sizeof(*res.ptr), cmp);
    return res.ptr;
}
