typedef ptrdiff_t isize;

static inline isize abs_isize(const isize a)
{
    return a < 0 ? -a : a;
}

enum state : int8_t{
    STATE_NONE = 0,
    STATE_IN_PROCESS,
    STATE_SEEN
};

static inline isize calc_next_idx(const isize curr, const isize len, const int num)
{
    return (((curr + num) % len) + len) % len;
}

bool circularArrayLoop(int* nums, const int nums_len)
{
    assert(nums_len >= 0);
    if (nums_len <= 1) { return false; }
    assert(nums != NULL);
    const isize len = nums_len;
    enum state* states = calloc((size_t)len, sizeof(*states));
    assert(states != NULL);
    bool res = false;

    for (isize i = 0; i < len; i += 1) {
        if (states[i] == STATE_NONE) {
            isize curr = i;
            while (states[curr] == STATE_NONE) {
                states[curr] = STATE_IN_PROCESS;
                curr = calc_next_idx(curr, len, nums[curr]);
            }

            isize cycle_len = 0;
            const bool direction = nums[curr] > 0;
            bool valid = true;
            while (states[curr] == STATE_IN_PROCESS) {
                if ((nums[curr] > 0) != direction) {
                    valid = false;
                }
                states[curr] = STATE_SEEN;
                curr = calc_next_idx(curr, len, nums[curr]);
                cycle_len += 1;
            }

            if (valid && cycle_len > 1) {
                res = true;
                goto cleanup;
            }

            curr = i;
            while (states[curr] == STATE_IN_PROCESS){
                states[curr] = STATE_SEEN;
                curr = calc_next_idx(curr, len, nums[curr]);
            }
        }
    }

cleanup:
    free(states);
    return res;
}
