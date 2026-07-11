typedef ptrdiff_t isize;

static inline int32_t abs_int(const int32_t a)
{
    return a < 0 ? -a : a;
}

struct tuple {
    bool is_valid;
    int32_t n;
    int32_t d;
    isize new_start_idx;
};

static inline int32_t calc_gcd(int32_t a, int32_t b)
{
    while (b != 0) {
        const int32_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static inline struct tuple extract_nums(const char* s, const isize start_idx)
{
    if (s[start_idx] == '\0') {
        return (struct tuple){ false, 0, 0, 0 };
    }

    isize idx = start_idx;
    bool is_pos = true;
    if (s[idx] == '+') {
        idx += 1;
    } else if (s[idx] == '-') {
        is_pos = false;
        idx += 1;
    } else if (s[idx] > '9' || s[idx] < '0') {
        fprintf(stderr, "invalid input");
        exit(1);
    }

    int32_t n = 0;
    int32_t d = 0;

    while (s[idx] != '\0' && s[idx] != '/') {
        n = n * 10 + s[idx] - '0';
        idx += 1;
    }

    idx += 1;
    while (s[idx] != '\0' && s[idx] != '+' && s[idx] != '-') {
        d = d * 10 + s[idx] - '0';
        idx += 1;
    }

    return (struct tuple){ true, is_pos ? n : -n, d, idx};
}

char* fractionAddition(char* expression)
{
    assert(expression != NULL);
    int32_t n = 0;
    int32_t d = 1;
    isize start_idx = 0;
    while (true) {
        struct tuple res = extract_nums(expression, start_idx);
        if (!res.is_valid) {
            break;
        }
        const int32_t gcd = calc_gcd(res.d, d);
        const int32_t lcm = (res.d / gcd) * d;
        res.n = (lcm / res.d) * res.n;
        n = (lcm / d) * n;
        d = lcm;
        n += res.n;
        start_idx = res.new_start_idx;
    }

    const int32_t gcd = calc_gcd(abs_int(n), d);
    n /= gcd;
    d /= gcd;
    char* res = malloc(30 * sizeof(*res));
    assert(res != NULL);
    snprintf(res, 30, "%d/%d", n, d);

    return res;
}
