int longestWPI(const int* hours, const int len)
{
    assert(len >= 0 && len <= 10000);
    int16_t* prefix = malloc((size_t)(len + 2) * sizeof(*prefix));
    assert(prefix != NULL);
    for (int i = 0; i < len + 2; i += 1) { prefix[i] = -1; }
    int mid = len + 1;
    prefix[mid] = 0;
    int pos = mid;
    int res = 0;

    for (int i = 0; i < len; i += 1) {
        pos = hours[i] > 8 ? (pos + 1) : (pos - 1);
        if (pos > mid) {
            res = i + 1;
        } else {
            if (prefix[pos] == -1) {
                prefix[pos] = (int16_t)i;
            }

            if (prefix[pos - 1] != -1) {
                const int curr_width = i - prefix[pos - 1];
                if (curr_width > res) {
                    res = curr_width;
                }
            }
        }
    }

/* cleanup: */
    free(prefix);
    return res;
}
