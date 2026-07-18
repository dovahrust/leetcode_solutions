static inline size_t min_size(const size_t a, const size_t b)
{
    return a < b ? a : b;
}

int minFlips(const char* s)
{
    assert(s != NULL && s[0] != '\0');
    size_t ones = 0;
    size_t zeros = 0;
    char last_char = ' ';

    for (size_t i = 0; s[i] != '\0'; i += 1) {
        switch (s[i]) {
            case '0':
                zeros += 1;
                break;
            case '1':
                ones += 1;
                break;
            default:
                fprintf(stderr, "unreachable!(), invalid input");
                exit(1);
        }
        last_char = s[i];
    }

    if (zeros == 0 || ones <= 1) {
        return 0;
    }

    const size_t extra_keep_one = (s[0] == '1' && last_char == '1') ? 2 : 1;
    const size_t res = min_size(zeros, ones - extra_keep_one);

    assert(res <= (size_t)INT_MAX);

    return (int)res;
}
