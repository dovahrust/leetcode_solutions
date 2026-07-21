typedef ptrdiff_t isize;

class Solution {
public:
    static int maxActiveSectionsAfterTrade(const string_view s) {
        const isize len = std::ssize(s);
        isize total_ones = 0;
        isize prev_zeros = 0;
        isize curr_zeros = 0;
        isize max = 0;

        for (isize i = 0; i < len; ++i) {
            switch (s[i]) {
                case '0':
                    curr_zeros += 1;
                    if (prev_zeros > 0) {
                        max = std::max(max, prev_zeros + curr_zeros);
                    }
                    break;
                case '1':
                    if (i > 0 && s[i - 1] == '0') {
                        prev_zeros = curr_zeros;
                        curr_zeros = 0;
                    }
                    total_ones += 1;
                    break;
                default:
                    break;
            }
        }

        assert(max + total_ones <= numeric_limits<int>::max());
        return max + total_ones;
    }
};
