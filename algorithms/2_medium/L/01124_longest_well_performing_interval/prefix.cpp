class Solution {
public:
    static int longestWPI(const vector<int>& hours) {
        const ptrdiff_t len = std::ssize(hours);
        assert(len >= 0 && len <= 10000);
        auto prefix = vector<int16_t>(len + 2, -1);
        ptrdiff_t mid = len + 1;
        prefix[mid] = 0;
        ptrdiff_t pos = mid;
        int res = 0;

        for (ptrdiff_t i = 0; i < len; i += 1) {
            pos = hours[i] > 8 ? (pos + 1) : (pos - 1);
            if (pos > mid) {
                res = static_cast<int>(i + 1);
            } else {
                if (prefix[pos] == -1) {
                    prefix[pos] = static_cast<int16_t>(i);
                }

                if (prefix[pos - 1] != -1) {
                    const int curr_width = static_cast<int>(i) - prefix[pos - 1];
                    res = std::max(res, curr_width);
                }
            }
        }

        return res;
    }
};
