typedef ptrdiff_t isize;

static inline isize max_isize(const isize a, const isize b)
{
    return a > b ? a : b;
}

int maxActiveSectionsAfterTrade(const char* s)
{
    isize prev = 0;
    isize curr = 0;
    isize ones = 0;
    isize max = 0;

    for (isize i = 0; s[i] != '\0'; i += 1) {
        switch (s[i]) {
            case '1':
                ones += 1;
                if (i > 0 && s[i - 1] == '0') {
                    prev = curr;
                    curr = 0;
                }
                break;
            case '0':
                curr += 1;
                if (prev > 0) {
                    max = max_isize(max, curr + prev);
                }
                break;
            default:
                fprintf(stderr, "unreachable!() invalid input");
                exit(0);
        }
    }

    assert(max + ones <= INT_MAX);
    return max + ones;
}
