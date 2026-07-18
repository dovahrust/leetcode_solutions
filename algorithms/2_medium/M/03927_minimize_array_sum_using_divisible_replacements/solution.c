long long minArraySum(const int* nums, const int len)
{
    assert(len > 0 && nums != NULL);
    bool any_one = false;
    for (int i = 0; i < len; i += 1) {
        if (nums[i] == 1) {
            any_one = true;
            break;
        }
    }
    if (any_one) {
        return len;
    }

    int max = INT_MIN;
    for (int i = 0; i < len; i += 1) {
        assert(nums[i] >= 1 && nums[i] <= 100000);
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    int* freqs = calloc((size_t)(max + 1), sizeof(*freqs));
    assert(freqs != NULL);
    for (int i = 0; i < len; i += 1) {
        freqs[nums[i]] += 1;
    }
    for (int i = 0; i <= max; i += 1) {
        if (freqs[i] != 0) {
            int curr = i + i;
            while (curr <= max) {
                freqs[i] += freqs[curr];
                freqs[curr] = 0;
                curr += i;
            }
        }
    }

    int64_t res = 0;
    for (int i = 1; i <= max; i += 1) {
        res += i * (int64_t)freqs[i];
    }

/* cleanup: */
    free(freqs);
    return res;
}
