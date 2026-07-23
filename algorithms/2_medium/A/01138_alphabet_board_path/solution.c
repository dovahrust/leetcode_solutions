struct vec_char {
    char* ptr;
    size_t cap;
    size_t len;
};

static inline void vec_char_push_char(struct vec_char* vec, const char ch)
{
    if (vec->cap == vec->len) {
        const size_t new_cap = vec->cap == 0 ? 4 : vec->cap * 2;
        vec->ptr = realloc(vec->ptr, new_cap * sizeof(*vec->ptr));
        assert(vec->ptr != NULL);
        vec->cap = new_cap;
    }
    vec->ptr[vec->len] = ch;
    vec->len += 1;
}

static inline void vec_char_push_null(struct vec_char* vec)
{
    if (vec->cap == vec->len) {
        vec->cap += 1;
        vec->ptr = realloc(vec->ptr, vec->cap * sizeof(*vec->ptr));
        assert(vec->ptr != NULL);
    }
    vec->ptr[vec->len] = '\0';
    vec->len += 1;
}

char* alphabetBoardPath(char* target)
{
    int i = 0;
    int j = 0;
    struct vec_char res = { .ptr = NULL, .len = 0, .cap = 0 };

    for (size_t target_idx; target[target_idx] != '\0'; target_idx += 1) {
        const char ch = target[target_idx];
        assert(ch >= 'a' && ch <= 'z');
        const int new_i = (ch - 'a') / 5;
        const int new_j = (ch - 'a') % 5;

        while (j > new_j) {
            vec_char_push_char(&res, 'L');
            j -= 1;
        }

        while (i > new_i) {
            vec_char_push_char(&res, 'U');
            i -= 1;
        }

        while (i < new_i) {
            vec_char_push_char(&res, 'D');
            i += 1;
        }

        while (j < new_j) {
            vec_char_push_char(&res, 'R');
            j += 1;
        }

        vec_char_push_char(&res, '!');
    }

    vec_char_push_null(&res);
    return res.ptr;
}
