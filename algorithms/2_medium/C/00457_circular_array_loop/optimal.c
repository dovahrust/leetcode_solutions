typedef ptrdiff_t isize;

static inline isize abs_isize(const isize a)
{
    return a < 0 ? -a : a;
}

bool circularArrayLoop(int* nums, const int nums_len)
{
    assert(nums_len >= 0);
    if (nums_len <= 1) { return false; }
    assert(nums != NULL);
    const isize len = nums_len;
    int seen = INT_MAX;

    for (isize i = 0; i < len; i += 1) {
        seen -= 1;

        if (nums[i] < seen) {
            bool prev_is_pos = nums[i] >= 0;
            isize prev_idx = i;
            isize curr_idx = i;

            while (nums[curr_idx] < seen) {
                const bool curr_is_pos = nums[curr_idx] >= 0;
                if (curr_is_pos != prev_is_pos) {
                    seen -= 1;
                }
                prev_is_pos = curr_is_pos;

                const isize diff = abs_isize(nums[curr_idx]) % len;
                const isize next_idx = (nums[curr_idx] < 0 ? (curr_idx + len - diff) : (curr_idx + diff)) % len;

                nums[curr_idx] = seen;
                prev_idx = curr_idx;
                curr_idx = next_idx;
            }

            if (prev_idx != curr_idx && nums[prev_idx] == nums[curr_idx]) {
                return true;
            }
        }
    }

    return false;
}
