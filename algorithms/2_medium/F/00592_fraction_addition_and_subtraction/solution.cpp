typedef ptrdiff_t isize;

struct tuple_result {
    bool is_valid;
    int32_t n;
    int32_t d;
    isize new_start_idx;

    tuple_result(bool is_valid, int32_t n, int32_t d, isize new_start_idx) {
        this->is_valid = is_valid;
        this->n = n;
        this->d = d;
        this->new_start_idx = new_start_idx;
    }
};

class Solution {
    static inline tuple_result extract_nums(const string_view s, const isize start_idx) {
        const isize len = std::ssize(s);
        if (start_idx == len) {
            return tuple_result(false, 0, 0, 0);
        }

        isize idx = start_idx;
        bool is_pos = true;
        if (s[idx] == '+') {
            idx += 1;
        } else if (s[idx] == '-') {
            is_pos = false;
            idx += 1;
        } else if (s[idx] > '9' || s[idx] < '0') {
            cerr << "invalid input\n";
            exit(1);
        }

        int32_t n = 0;
        int32_t d = 0;

        while (idx < len && s[idx] != '/') {
            n = n * 10 + s[idx] - '0';
            idx += 1;
        }

        idx += 1;
        while (idx < len && s[idx] != '+' && s[idx] != '-') {
            d = d * 10 + s[idx] - '0';
            idx += 1;
        }

        return tuple_result(true, is_pos ? n : -n, d, idx);
    }
public:
    static string fractionAddition(const string& expression) {
        int32_t n = 0;
        int32_t d = 1;
        isize start_idx = 0;
        while (true) {
            auto res = extract_nums(expression, start_idx);
            if (!res.is_valid) {
                break;
            }
            const int32_t lcm = std::lcm(res.d, d);
            res.n = (lcm / res.d) * res.n;
            n = (lcm / d) * n;
            d = lcm;
            n += res.n;
            start_idx = res.new_start_idx;
        }

        const int32_t gcd = std::gcd(std::abs(n), d);
        n /= gcd;
        d /= gcd;

        return format("{}/{}", n, d);
    }
};
