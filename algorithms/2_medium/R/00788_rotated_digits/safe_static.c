#define MAX_ALLOWED_N 10000
#define VALIDS_LEN 3
#define VALIDS_WITH_DIFF_LEN 4

static const int8_t VALIDS[VALIDS_LEN] = { 0, 1, 8 };
static const int8_t VALIDS_WITH_DIFF[VALIDS_WITH_DIFF_LEN] = { 2, 5, 6, 9 };

static pthread_once_t once_init = PTHREAD_ONCE_INIT;
static int16_t freqs[MAX_ALLOWED_N + 1] = { 0 };

void init_backtrack(const int a, const bool contains_diff)
{
    if (a > MAX_ALLOWED_N) {
        return;
    }

    if (contains_diff) {
        freqs[a] = 1;
    }

    const int base = a * 10;

    for (size_t i = 0; i < VALIDS_LEN; i += 1) {
        init_backtrack(base + VALIDS[i], contains_diff);
    }

    for (size_t i = 0; i < VALIDS_WITH_DIFF_LEN; i += 1) {
        init_backtrack(base + VALIDS_WITH_DIFF[i], true);
    }
}

void init(void)
{
    for (size_t i = 0; i < VALIDS_LEN; i += 1) {
        if (VALIDS[i] != 0) {
            init_backtrack(VALIDS[i], false);
        }
    }

    for (size_t i = 0; i < VALIDS_WITH_DIFF_LEN; i += 1) {
        init_backtrack(VALIDS_WITH_DIFF[i], true);
    }

    for (size_t i = 1; i <= MAX_ALLOWED_N; i += 1) {
        freqs[i] += freqs[i - 1];
    }
}

int rotatedDigits(int n)
{
    assert(n <= MAX_ALLOWED_N && n >= 1);
    pthread_once(&once_init, init);
    return freqs[n];
}
