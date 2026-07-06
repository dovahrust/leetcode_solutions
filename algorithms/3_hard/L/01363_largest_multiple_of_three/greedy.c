#define IDXS_REM1_LEN 3
#define IDXS_REM2_LEN 3

typedef ptrdiff_t isize;

static const isize idxs_rem1[IDXS_REM1_LEN] = {1, 4, 7};
static const isize idxs_rem2[IDXS_REM2_LEN] = {2, 5, 8};

static void decrease_cnt_from_freqs(isize* freqs, const isize* idxs, const isize idxs_len, int cnt)
{
    assert(cnt > 0);
    for (isize i = 0; i < idxs_len; i += 1) {
        const isize idx = idxs[i];

        while (freqs[idx] > 0 && cnt > 0) {
            freqs[idx] -= 1;
            cnt -= 1;
        }

        if (cnt == 0) {
            return;
        }
    }

    fprintf(stderr, "logical error, unreachable()!\n");
    exit(1);
}

char* largestMultipleOfThree(int* digits, int digits_len)
{
    assert(digits_len >= 0);
    const isize len = digits_len;
    isize freqs[10] = { 0 };
    isize rems[3] = { 0 };
    int sum = 0;
    for (isize i = 0; i < len; i += 1) {
        const int d = digits[i];
        assert(d >= 0 && d <= 9);
        sum += d;
        freqs[d] += 1;
        rems[(d % 3)] += 1;
    }

    switch (sum % 3) {
        case 1:
            if (rems[1] > 0) {
                decrease_cnt_from_freqs(freqs, idxs_rem1, IDXS_REM1_LEN, 1);
            } else if (rems[2] > 1) {
                decrease_cnt_from_freqs(freqs, idxs_rem2, IDXS_REM2_LEN, 2);
            } else {
                fprintf(stderr, "logical error, unreachable()!\n");
                exit(1);
            }
            break;
        case 2: 
            if (rems[2] > 0) {
                decrease_cnt_from_freqs(freqs, idxs_rem2, IDXS_REM2_LEN, 1);
            } else if (rems[1] > 1) {
                decrease_cnt_from_freqs(freqs, idxs_rem1, IDXS_REM1_LEN, 2);
            } else {
                fprintf(stderr, "logical error, unreachable()!\n");
                exit(1);
            }
            break;
        default:
            break;
    }

    bool any_non_zero = false;
    for (isize i = 1; i < 10; i += 1) {
        if (freqs[i] != 0) {
            any_non_zero = true;
            break;
        }
    }
    if (!any_non_zero) {
        if (freqs[0] > 0) {
            char* res = malloc(2 * sizeof(*res));
            assert(res != NULL);
            res[0] = '0';
            res[1] = '\0';
            return res;
        } else {
            char* res = malloc(sizeof(*res));
            assert(res != NULL);
            res[0] = '\0';
            return res;
        }
    }

    isize total_freqs = 0;
    for (isize i = 0 ; i < 10; i += 1) { total_freqs += freqs[i]; }
    char* res = malloc((size_t)(total_freqs + 1) * sizeof(*res));
    assert(res != NULL);
    res[total_freqs] = '\0';
    isize idx = 0;
    for (isize i = 9 ; i >= 0; i -= 1) {
        const isize total_steps = freqs[i];
        for (isize steps = 0; steps < total_steps; steps += 1) {
            res[idx] = (char)((int)i + '0');
            idx += 1;
        }
    }
    return res;
}
