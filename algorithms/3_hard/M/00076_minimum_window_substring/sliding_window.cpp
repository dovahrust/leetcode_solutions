typedef ptrdiff_t isize;

class Solution {
    static inline bool is_ok(const span<const isize> freqs) {
        for (char ch = 'A'; ch <= 'z'; ch += 1) {
            if (freqs[ch] < 0) {
                return false;
            }
        }
        return true;
    }

public:
    static string minWindow(const string& s, const string& t) {
        const isize s_len = std::ssize(s);
        if (s_len < std::ssize(t)) { return string(); }
        isize freqs[256] = { 0 };

        for (const auto ch : t) {
            freqs[ch] -= 1;
        }

        isize lo = 0;
        auto res = span<const char>(&s[0], 0);

        for (isize hi = 0; hi < s_len; hi += 1) {
            freqs[s[hi]] += 1;

            while (lo <= hi && freqs[s[lo]] > 0) {
                freqs[s[lo]] -= 1;
                lo += 1;
            }

            if ((res.empty() || std::ssize(res) > ((hi + 1) - lo)) && is_ok(freqs)) {
                res = span<const char>(&s[lo], (hi + 1) - lo);
            }
        }

        return string(res.cbegin(), res.cend());
    }
};
