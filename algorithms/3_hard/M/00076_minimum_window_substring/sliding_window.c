typedef ptrdiff_t isize;

static inline bool is_ok(const isize* freqs)
{
    for (int ch = 'A'; ch <= 'z'; ch += 1) {
        if (freqs[ch] < 0) {
            return false;
        }
    }
    return true;
}

char* minWindow(char* s, char* t)
{
    isize freqs[256] = { 0 };

    for (isize i = 0; t[i] != '\0'; i += 1) {
        freqs[(unsigned char)t[i]] -= 1;
    }

    isize lo = 0;
    isize res_start_idx = 0;
    isize res_len = 0;

    for (isize hi = 0; s[hi] != '\0'; hi += 1) {
        freqs[(unsigned char)s[hi]] += 1;

        while (lo <= hi && freqs[s[lo]] > 0) {
            freqs[(unsigned char)s[lo]] -= 1;
            lo += 1;
        }

        if ((res_len == 0 || res_len > ((hi + 1) - lo)) && is_ok(freqs)) {
            res_start_idx = lo;
            res_len = (hi + 1) - lo;
        }
    }

    char* res = malloc((size_t)(res_len + 1) * sizeof(*res));
    assert(res != NULL);
    res[res_len] = '\0';
    for (isize i = res_start_idx; i < res_start_idx + res_len; i += 1) {
        res[i - res_start_idx] = s[i];
    }
    return res;
}
