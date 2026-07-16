typedef ptrdiff_t isize;

int minOperations(const char* s1, const char* s2)
{
    const size_t len = strlen(s1);
    assert(len > 0 && len == strlen(s2));

    if (len == 1 && s1[0] == '1' && s2[0] == '0') {
        return -1;
    }

    isize cnt = 0;
    size_t i = 0;

    while (i < len) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                if (i + 1 < len && s1[i + 1] == '1' && s2[i + 1] == '0') {
                    cnt += 1;
                    i += 2;
                } else {
                    cnt += 2;
                    i += 1;
                }
            } else {
                cnt += 1;
                i += 1;
            }
        } else {
            i += 1;
        }
    }

    assert(cnt <= INT_MAX);
    return (int)cnt;
}
