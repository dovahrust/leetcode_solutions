#define MAX_ALLOWED_PRICE 10000
#define MAX_ALLOWED_N 100
#define MAX_ALLOWED_FLIGHTS ((MAX_ALLOWED_N * (MAX_ALLOWED_N - 1)) / 2)
#define INF (INT_MAX / 2)

static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

int findCheapestPrice(int n, int** flights, int flights_len, int* flights_col_lem, int src, int dst, int k)
{
    assert(k >= 0 && k < n && n <= MAX_ALLOWED_N && flights_len <= MAX_ALLOWED_FLIGHTS);
    assert(src >= 0 && src < n && dst >= 0 && dst < n && src != dst);

    int* buff = malloc((size_t)(2 * n) * sizeof(*buff));
    assert(buff != NULL);
    int* curr = &buff[0];
    int* next = &buff[n];
    for (int i = 0; i < n; i += 1) {
        curr[i] = INF;
        next[i] = INF;
    }
    curr[src] = 0;
    next[src] = 0;

    for (int stops = 0; stops <= k; stops += 1) {
        for (int i = 0; i < flights_len; i += 1) {
            const int* f = flights[i];
            const int u = f[0];
            const int v = f[1];
            const int w = f[2];
            assert(u >= 0 && u < n && v >=0 && v < n && w >= 1 && w <= MAX_ALLOWED_PRICE);
            next[v] = min_int(next[v], curr[u] + w);
        }
        int* temp = curr;
        curr = next;
        next = temp;
    }

    const int res = curr[dst] == INF ? -1 : curr[dst];
/* cleanup: */
    free(buff);
    return res;
}
