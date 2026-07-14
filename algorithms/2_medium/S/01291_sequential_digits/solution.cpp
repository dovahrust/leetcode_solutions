constexpr int max_hi = 1'000'000'000;

class Solution {
public:
    static vector<int> sequentialDigits(const int lo, const int hi) {
        assert(lo >= 10 && lo <= hi && hi <= max_hi);
        auto res = vector<int>();

        for (int start_dig = 1; start_dig <= 9; start_dig += 1) {
            int num = 0;

            for (int dig = start_dig; dig <= 9; dig += 1) {
                num = num * 10 + dig;

                if (num > hi) {
                    break;
                }

                if (num >= lo) {
                    res.push_back(num);
                }
            }
        }

        ranges::sort(res);
        return res;
    }
};
