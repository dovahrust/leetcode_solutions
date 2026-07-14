#define MOD 1000000007

static inline int gcd(int a, int b)
{
    while (b != 0) {
        const int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int subsequencePairCount(const int* nums, const int len)
{
    assert(len >= 1 && len <= 200 && nums != NULL);
    if (len == 1) {
        return 0;
    }

    int max = 0;
    for (int i = 0; i < len; i += 1) {
        assert(nums[i] >= 1 && nums[i] <= 200);
        const int num = nums[i];
        max = num > max ? num : max;
    }

    const int rows = max + 1;
    const int cols = max + 1;
    int* buff = calloc(2 * (size_t)rows * (size_t)cols, sizeof(*buff));
    assert(buff != NULL);
    int* curr = &buff[0];
    int* next = &buff[rows * cols];
    curr[0] = 1;

    for (int i = 0; i < len; i += 1) {
        const int num = nums[i];

        for (int j = 0; j < rows * cols; j += 1) {
            next[j] = curr[j];
        }

        for (int g1 = 0; g1 <= max; g1 += 1) {
            for(int g2 = 0; g2 <= max; g2 += 1) {
                const int cnt = curr[g1 * cols  + g2];
                if (cnt == 0) { continue; }

                const int idx_g1_pick = gcd(g1, num) * cols + g2;
                const int idx_g2_pick = g1 * cols + gcd(g2, num);

                next[idx_g1_pick] = (next[idx_g1_pick] + cnt) % MOD;
                next[idx_g2_pick] = (next[idx_g2_pick] + cnt) % MOD;
            }
        }

        int* temp = curr;
        curr = next;
        next = temp;
    }

    int res = 0;

    for (int i = 1; i <= max; i += 1) {
        res = (res + curr[i * cols + i ]) % MOD;
    }
/* cleanup: */
    free(buff);
    return res;
}
