struct pair {
    int num;
    int idx;
};

static int cmp(const void* a_ptr, const void* b_ptr)
{
    const struct pair* a = (const struct pair*)a_ptr;
    const struct pair* b = (const struct pair*)b_ptr;
    return (a->num > b->num) - (a->num < b->num);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* arrayRankTransform(const int* arr, const int len, int* return_len)
{
    assert(return_len != NULL);
    if (arr == NULL || len == 0) {
        *return_len = 0;
        return NULL;
    }

    *return_len = len;
    struct pair* combo = malloc((size_t)len * sizeof(*combo));
    assert(combo != NULL);
    for (int i = 0; i < len; i += 1) {
        combo[i].num = arr[i];
        combo[i].idx = i;
    }
    qsort(combo, (size_t)len, sizeof(*combo), cmp);

    int* ranks = malloc((size_t)len * sizeof(*ranks));
    assert(ranks != NULL);
    int rank = 1;
    ranks[combo[0].idx] = rank;
    for (int i = 1; i < len; i += 1) {
        if (combo[i].num > combo[i - 1].num) {
            rank += 1;
        }

        ranks[combo[i].idx] = rank;
    }

/* cleanup: */
    free(combo);
    return ranks;
}
