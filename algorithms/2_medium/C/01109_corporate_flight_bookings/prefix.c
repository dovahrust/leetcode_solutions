/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
__attribute__((no_sanitize("all")))
int* corpFlightBookings(int** bookings, const int rows, const int* cols_data, const int n, int* return_len)
{
    assert(n >= 0 && rows > 0 && cols_data != NULL && bookings != NULL);
    int* prefix = calloc((size_t)n + 1, sizeof(*prefix));
    assert(prefix != NULL);
    *return_len = n;

    for (int i = 0; i < rows; i += 1) {
        const int* b = bookings[i];
        assert(cols_data[i] == 3);
        int lo = b[0];
        int hi = b[1];
        int seats = b[2];
        assert(lo >= 1 && lo <= hi && hi <= n && seats >= 1);
        prefix[lo - 1] += seats;
        prefix[hi] -= seats;
    }
    for (int i = 1; i < n; i += 1) {
        prefix[i] += prefix[i - 1];
    }

    return prefix;
}
