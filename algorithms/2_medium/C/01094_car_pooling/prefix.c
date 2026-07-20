#define MAX_DEST 1000

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

bool carPooling(int** trips, const int rows, const int* cols_data, const int capacity)
{
    assert(rows >= 0 && rows <= 1000);
    if (rows == 0)  { return true; }

    int max = 0;
    for (int i = 0; i < rows; i += 1) {
        const int* t = trips[i];
        assert(
            cols_data[i] == 3 &&
            t[0] > 0 && t[0] <= 100 &&
            0 <= t[1] && t[1] < t[2] && t[2] <= MAX_DEST
        );
        max = max_int(max, t[2]);
    }

    int* prefix = calloc((size_t)max + 1, sizeof(*prefix));
    assert(prefix != NULL);

    for (int i = 0; i < rows; i += 1) {
        const int* t = trips[i];
        prefix[t[1]] += t[0];
        prefix[t[2]] -= t[0];
    }

    if (prefix[0] > capacity) {
        return false;
    }

    bool res = true;
    for (int i = 1; i < max + 1; i += 1) {
        prefix[i] += prefix[i - 1];
        if (prefix[i] > capacity) {
            res = false;
            break;
        }
    }

/* cleanup: */
    free(prefix);
    return res;
}
