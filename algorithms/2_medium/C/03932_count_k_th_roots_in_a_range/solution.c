static inline int64_t pow_int64(int64_t base, uint32_t exp) {
    int64_t res = 1;
    while (exp != 0) {
        if (exp & 1) {
            res *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return res;
}

int countKthRoots(const int l_i32, const int r_i32, const int k_i32)
{
    assert(k_i32 >= 1 && l_i32 <= r_i32 && l_i32 >= 0);
    const int64_t l = l_i32;
    const int64_t r = r_i32;
    const uint32_t k = (uint32_t)k_i32;
    if (k == 1) {
        return (int)(r - l + 1);
    }
    int cnt = 0;
    int64_t curr = 0;
    while (true) {
        const int64_t pow_val = pow_int64(curr, k);
        if (pow_val > r) {
            break;
        }
        if (pow_val >= l) {
            cnt += 1;
        }
        curr += 1;
    }
    return cnt;
}
