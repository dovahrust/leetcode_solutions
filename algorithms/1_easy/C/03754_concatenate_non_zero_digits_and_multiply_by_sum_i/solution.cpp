class Solution {
public:
    long long sumAndMultiply(int n) {
        assert(n >= 0);
        int64_t sum = 0;
        int64_t res = 0;
        int p = 1;

        while (n / p >= 10) {
            p *= 10;
        }

        while (p > 0) {
            const int dig = (n / p) % 10;
            p /= 10;

            if (dig > 0) {
                res *= 10;
                res += dig;
                sum += dig;
            }
        }

        return res * sum;
    }
};
