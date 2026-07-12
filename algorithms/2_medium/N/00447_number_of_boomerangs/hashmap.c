#define MAX_ALLOWED_LEN 500
#define MAX_ALLOWED_NUM 10000
#define MIN_ALLOWED_NUM -10000
#define TABLE_LEN (MAX_ALLOWED_LEN * 2)

struct entity {
    int key;
    int freq;
};

static inline int calc_diff_sq(const int* a, const int* b)
{
    const int dx = a[0] - b[0];
    const int dy = a[1] - b[1];
    return (dx * dx)  + (dy * dy);
}

int numberOfBoomerangs(int** points, const int len, int* points_col_len)
{
    assert(len >= 0 && len <= MAX_ALLOWED_LEN);
    if (len <= 2) { return 0; }
    assert(points != NULL && points_col_len != NULL);
    for (int i = 0; i < len; i += 1) {
        const int* p = points[i];
        assert(points_col_len[i] == 2 &&
               p[0] >= MIN_ALLOWED_NUM && p[0] <= MAX_ALLOWED_NUM &&
               p[1] >= MIN_ALLOWED_NUM && p[1] <= MAX_ALLOWED_NUM);
    }

    int cnt = 0;
    struct entity* table = malloc((size_t)TABLE_LEN * sizeof(*table));
    assert(table != NULL);
    for (int i = 0; i < TABLE_LEN; i += 1) {
        table[i].freq = 0;
    }

    for (int i = 0; i < len; i += 1) {
        for (int j = 0; j < len; j += 1) {
            if (j == i) { continue; }
            const int diff_sq = calc_diff_sq(points[i], points[j]);
            int idx = diff_sq % TABLE_LEN;
            while (table[idx].freq != 0) {
                if (table[idx].key == diff_sq) { break; }
                idx = (idx + 1) % TABLE_LEN;
            }
            table[idx].key = diff_sq;
            table[idx].freq += 1;
        }
        for (int i = 0; i < TABLE_LEN; i += 1) {
            cnt += table[i].freq * (table[i].freq - 1);
            table[i].freq = 0;
        }
    }

/* cleanup: */
    free(table);
    return cnt;
}
