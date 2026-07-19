char* smallestSubsequence(const char* s)
{
    const size_t len = strlen(s);
    assert(len >= 1 && len <= 1000);
    char* stack = malloc((len + 1) * sizeof(*s));
    size_t stack_len = 0;
    assert(stack != NULL);
    uint16_t freqs[26] = { 0 };

    for (size_t i = 0; i < len; i += 1) {
        const char ch = s[i];
        assert(ch >= 'a' && ch <= 'z');
        freqs[ch - 'a'] += 1;
    }

    bool seen[26] = { false };

    for (size_t i = 0; i < len; i += 1) {
        const char ch = s[i];
        if (!seen[ch - 'a']) {
            while (stack_len > 0 && stack[stack_len - 1] >= ch && freqs[stack[stack_len - 1] - 'a'] >= 1) {
                seen[stack[stack_len - 1] - 'a'] = false;
                stack_len -= 1;
            }
            seen[ch - 'a'] = true;
            stack[stack_len] = ch;
            stack_len += 1;
        }
        freqs[ch - 'a'] -= 1;
    }

    stack[stack_len] = '\0';
    return stack;
}
