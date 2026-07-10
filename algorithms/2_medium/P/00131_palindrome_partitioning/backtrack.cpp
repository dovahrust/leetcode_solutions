typedef ptrdiff_t isize;

class Solution {
    static inline bool is_palindrome(const span<const char> s) {
        isize hi = std::ssize(s) - 1;
        isize lo = 0;

        while (lo < hi) {
            if (s[lo] != s[hi]) {
                return false;
            }

            lo += 1;
            hi -= 1;
        }

        return true;
    }

    static void backtrack(const string_view s, const isize lo, vector<vector<string>>& res, vector<string>& temp) {
        const isize len = std::ssize(s);

        if (lo >= len) {
            res.push_back(temp);
            return;
        }

        for (isize hi = lo; hi < len; hi += 1) {
            if (is_palindrome(span<const char>(&s[lo], hi - lo + 1))) {
                temp.push_back(string(s.cbegin() + lo, s.cbegin() + hi + 1));
                backtrack(s, hi + 1, res, temp);
                temp.pop_back();
            }
        }
    }
public:
    static vector<vector<string>> partition(const string& s) {
        auto res = vector<vector<string>>();
        auto temp = vector<string>();

        backtrack(s, 0, res, temp);

        return res;
    }
};
