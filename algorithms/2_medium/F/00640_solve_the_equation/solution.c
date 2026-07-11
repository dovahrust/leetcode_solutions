typedef ptrdiff_t isize;

enum extract_state {
    IS_NUM,
    IS_X,
    IS_EQ,
    NONE
};

struct extract_result {
    enum extract_state state;
    int32_t val;
    isize new_start_idx;
};

static inline struct extract_result extract_nums(const char* s, isize idx)
{
    if (s[idx] == '\0') {
        return (struct extract_result){ NONE, 0, 0 };
    }

    if (s[idx] == '=') {
        return (struct extract_result){ IS_EQ, 0, idx + 1 };
    }

    bool is_pos = true;
    if (s[idx] == '+') {
        idx += 1;
    } else if (s[idx] == '-') {
        is_pos = false;
        idx += 1;
    } else if ((s[idx] > '9' || s[idx] < '0') && s[idx] != 'x') {
        fprintf(stderr, "invalid input");
        exit(1);
    }

    if (s[idx] == 'x') {
        return (struct extract_result){ IS_X, (is_pos ? 1 : -1), idx + 1 };
    }

    int32_t num = 0;
    while (s[idx] >= '0' && s[idx] <= '9') {
        num = num * 10 + s[idx] - '0';
        idx += 1;
    }

    if (s[idx] == 'x') {
        return (struct extract_result){ IS_X, (is_pos ? num : -num), idx + 1 };
    }

    return (struct extract_result){ IS_NUM, (is_pos ? num : -num), idx };
}

char* solveEquation(char* equation)
{
    isize start_idx = 0;
    bool is_left_op = true;
    int32_t num = 0;
    int32_t x = 0;
    bool no_more_tokens = false;
    while (!no_more_tokens) {
        struct extract_result res = extract_nums(equation, start_idx);

        switch (res.state) {
            case (IS_NUM):
                num += is_left_op ? res.val : -res.val;
                start_idx = res.new_start_idx;
                break;
            case (IS_X):
                x += is_left_op ? res.val : -res.val;
                start_idx = res.new_start_idx;
                break;
            case IS_EQ:
                is_left_op = false;
                start_idx = res.new_start_idx;
                break;
            case NONE:
                no_more_tokens = true;
                break;
            default:
                break;
        }
    }

    char* res = malloc(30 * sizeof(*res));
    assert(res != NULL);

    if (x == 0) {
        if (num == 0) {
            snprintf(res, 30, "Infinite solutions");
        } else {
            snprintf(res, 30, "No solution");
        }
    } else {
        snprintf(res, 30, "x=%d", -num / x);
    }

    return res;
}
