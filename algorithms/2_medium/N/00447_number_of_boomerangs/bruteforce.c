#define MAX_ALLOWED_LEN 500
#define MAX_ALLOWED_NUM 10000
#define MIN_ALLOWED_NUM -10000

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

    for (int i = 0; i < len; i += 1) {
        for (int j = i + 1; j < len; j += 1) {
            const int d1 = calc_diff_sq(points[i], points[j]);
            for (int k = j + 1; k < len; k += 1) {
                const int d2 = calc_diff_sq(points[i], points[k]);
                const int d3 = calc_diff_sq(points[j], points[k]);

                if (d1 == d2) {
                    cnt += 2;
                }

                if (d1 == d3) {
                    cnt += 2;
                }

                if (d2 == d3) {
                    cnt += 2;
                }
            }
        }
    }

    return cnt;
}
