static inline int16_t max_int16(const int16_t a, const int16_t b)
{
    return a > b ? a : b;
}

static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

static inline bool is_ok(int** grid, const int rows, const int cols,
                        const int lo, const int hi, int limit)
{
    for (int i = 0; i < rows; i += 1) {
        if (abs_int(grid[i][hi] - grid[i][lo]) > limit) {
            return false;
        }
    }
    return true;
}

int maxConsistentColumns(int** grid, const int rows, const int* all_cols, int limit)
{
    assert(rows >= 1 && all_cols != NULL && all_cols[0] >= 1 && all_cols[0] <= 250 && grid != NULL);
    const int cols = all_cols[0];
    int16_t* dp = malloc((size_t)cols * sizeof(*dp));
    assert(dp != NULL);
    for (int i = 0; i < cols; i += 1) {
        dp[i] = 1;
    }

    for (int i = 0; i < cols; i += 1) {
        for (int j = 0; j < i; j += 1) {
            if (is_ok(grid, rows, cols, j, i, limit)) {
                dp[i] = max_int16(dp[i], 1 + dp[j]);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < cols; i += 1) {
        res = max_int16(res, dp[i]);
    }

/* cleanup: */
    free(dp);
    return res;
}
