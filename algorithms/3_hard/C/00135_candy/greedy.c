static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int candy(int* ratings, int len)
{
    assert(len > 0 && len <= 2 * 10000 && ratings != NULL);
    int* vec = malloc((size_t)len * sizeof(*vec));
    assert(vec != NULL);
    for (int i = 0; i < len; i += 1) { vec[i] = 1; }
    int cnt = 0;

    for (int i = 1; i < len; i +=1) {
        if (ratings[i - 1] < ratings[i]) {
            vec[i] = vec[i - 1] + 1;
        }
    }

    for (int i = len - 1; i > 0; i -=1) {
        if (ratings[i - 1] > ratings[i]) {
            vec[i - 1] = max_int(vec[i - 1], vec[i] + 1);
        }
        cnt += vec[i - 1];
    }
    cnt += vec[len - 1];

/* cleanup: */
    free(vec);
    return cnt;
}
