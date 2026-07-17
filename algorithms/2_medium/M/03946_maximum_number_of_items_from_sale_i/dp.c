static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

static int max_factor(int** items, const int items_len)
{
    int res = INT_MIN;
    for (int i = 0; i < items_len; i += 1) {
        assert(items[i][0] >= 1 && items[i][0] <= 1500);
        res = max_int(res, items[i][0]);
    }
    return res;
}


int maximumSaleItems(int** items, const int items_len, const int* items_cols_len, const int budget)
{
    assert(budget >= 1 && budget<= 1500 && items_len > 0 &&
           items != NULL && items_cols_len != NULL && items_cols_len[0] == 2);
    const int max = max_factor(items, items_len);
    int* buff = calloc((size_t)(2 * (max + 1) + 2 * (budget + 1)), sizeof(*buff));
    int* extra = &buff[0];
    int* freqs = &buff[1 + max];
    int* curr = &buff[2 * (1 + max)];
    int* next = &buff[2 * (1 + max) + 1 + budget];

    for (int i = 0; i < items_len; i += 1) {
        freqs[items[i][0]] += 1;
    }

    for (int i = 1; i <= max; i += 1) {
        int curr = i;
        while (curr <= max) {
            extra[i] += freqs[curr];
            curr += i; 
        }
    }

    for (int i = 0; i < items_len; i += 1) {
        const int price_i = items[i][1];
        if (price_i > budget) {
            continue;
        }
        const int cnt = extra[items[i][0]];
        for (int j = price_i; j <= budget; j += 1) {
            next[j] = max_int(next[j], curr[j - price_i] + cnt);
            next[j] = max_int(next[j], next[j - price_i] + 1);
        }
        for (int idx = 1; idx <= budget; idx += 1) {
            curr[idx] = next[idx];
        }
    }

/* cleanup: */
    const int res = curr[budget];
    free(buff);
    return res; 
}
