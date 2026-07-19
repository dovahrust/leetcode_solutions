typedef ptrdiff_t isize;

static void reverse(char* s, isize lo, isize hi)
{
    while (lo < hi) {
        const char temp = s[lo];
        s[lo] = s[hi];
        s[hi] = temp;
        lo += 1;
        hi -= 1;
    }
}

char* reverseParentheses(char* s)
{
    assert(s != NULL && s[0] != '\0');
    const isize len = (isize)strlen(s);
    assert(len <= 2000);
    int16_t* stack = malloc((size_t)len * sizeof(*stack));
    char* res = malloc((size_t)(len + 1) * sizeof(*res));
    assert(res != NULL && stack != NULL);
    isize res_len = 0;
    isize stack_len = 0;

    for (isize i = 0; i < len; i += 1) {
        if (s[i] == '(') {
            stack[stack_len] = (int16_t)res_len;
            stack_len += 1;
        } else if (s[i] == ')') {
            assert(stack_len > 0 && "invalid input");
            isize lo = stack[stack_len - 1];
            stack_len -= 1;
            isize hi = res_len - 1;
            reverse(res, lo, hi);
        } else {
            res[res_len] = s[i];
            res_len += 1;
        }
    }

    res[res_len] = '\0';

    return res;
}
