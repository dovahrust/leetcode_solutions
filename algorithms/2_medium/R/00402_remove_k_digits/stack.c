typedef ptrdiff_t isize;

static inline isize min_isize(const isize a, const isize b)
{
    return a < b ? a : b;
}

char* removeKdigits(char* num, int k)
{
    assert(num != NULL && num[0] != '\0');
    isize stack_len = 0;

    for (isize i = 0; num[i] != '\0'; i += 1) {
        while (k > 0 && stack_len > 0 && num[stack_len - 1] > num[i]) {
            stack_len -= 1;
            k -= 1;
        }

        if (stack_len == 0 && num[i] == '0') {
            continue;
        }

        num[stack_len] = num[i];
        stack_len += 1;
    }

    stack_len -= min_isize(stack_len, k);

    if (stack_len == 0) {
        num[stack_len] = '0';
        stack_len += 1;
    }

    num[stack_len] = '\0';

    return num;
}
