#define INC 1
#define DEC -1

typedef ptrdiff_t isize;

static inline void update_freqs_and_mask(isize* freqs, const isize idx, const isize amount, isize* mask_non_zeros)
{
    freqs[idx] += amount;
    if (freqs[idx] == 0) {
        *mask_non_zeros &= ~(1 << idx);
    } else {
        *mask_non_zeros |= (1 << idx);
    }
}

bool checkInclusion(char* s1, char* s2)
{
    assert(s1 != NULL && s2 != NULL);
    const isize s1_len = (isize)strlen(s1);
    const isize s2_len = (isize)strlen(s2);
    assert(s1_len > 0 && s2_len > 0);
    if (s2_len < s1_len) { return false; }

    isize freqs[26] = { 0 };
    isize mask_non_zeros = 0;

    for (isize i = 0; i < s1_len; i += 1) {
        assert(s1[i] >= 'a' && s1[i] <= 'z');
        update_freqs_and_mask(freqs, s1[i] - 'a', DEC, &mask_non_zeros);
    }

    for (isize i = 0; i < s2_len; i += 1) {
        assert(s2[i] >= 'a' && s2[i] <= 'z');
        update_freqs_and_mask(freqs, s2[i] - 'a', INC, &mask_non_zeros);
        if (i >= s1_len) {
            update_freqs_and_mask(freqs, s2[i - s1_len] - 'a', DEC, &mask_non_zeros);
        }

        if (mask_non_zeros == 0) {
            return true;
        }
    }

    return false;
}
