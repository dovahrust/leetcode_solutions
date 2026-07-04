typedef ptrdiff_t isize;

static const isize* min_element(const isize* arr, isize len)
{
    if (arr == NULL || len <= 0) { return arr; }
    const isize* min = &arr[0];

    for (isize i = 0; i < len; i += 1) {
        if (*min > arr[i]) {
            min = &arr[i];
        }
    }

    return min;
}

int numberOfSubstrings(char* s)
{
    assert(s != NULL);
    isize last_seen[3] = { -1, -1, -1};
    isize cnt = 0;

    for (isize idx = 0; s[idx] != '\0'; idx += 1) {
        const char ch = s[idx];
        assert(ch >= 'a' && ch <= 'c');
        last_seen[ch - 'a'] = idx;
        cnt += 1 + *min_element(last_seen, 3);
    }

    assert(cnt <= INT_MAX);
    return (int)cnt;
}
