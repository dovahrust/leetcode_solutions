typedef ptrdiff_t isize;

constexpr isize idxs_rem1[3] = {1, 4, 7};
constexpr isize idxs_rem2[3] = {2, 5, 8};

static void decrease_cnt_from_freqs(span<isize> freqs, const span<const isize> idxs, int cnt) {
    assert(cnt > 0);
    for (const auto idx : idxs) {
        while (freqs[idx] > 0 && cnt > 0) {
            freqs[idx] -= 1;
            cnt -= 1;
        }

        if (cnt == 0) {
            return;
        }
    }

    cerr << "logical error, unreachable()!\n";
    exit(1);
}

class Solution {
public:
    static string largestMultipleOfThree(const vector<int>& digits) {
        isize freqs[10] = { 0 };
        isize rems[3] = { 0 };
        int sum = 0;
        for (const int d : digits) {
            assert(d >= 0 && d <= 9);
            sum += d;
            freqs[d] += 1;
            rems[(d % 3)] += 1;
        }

        switch (sum % 3) {
            case 1:
                if (rems[1] > 0) {
                    decrease_cnt_from_freqs(freqs, idxs_rem1, 1);
                } else if (rems[2] > 1) {
                    decrease_cnt_from_freqs(freqs, idxs_rem2, 2);
                } else {
                    cerr << "logical error, unreachable()!\n";
                    exit(1);
                }
                break;
            case 2: 
                if (rems[2] > 0) {
                    decrease_cnt_from_freqs(freqs, idxs_rem2, 1);
                } else if (rems[1] > 1) {
                    decrease_cnt_from_freqs(freqs, idxs_rem1, 2);
                } else {
                    cerr << "logical error, unreachable()!\n";
                    exit(1);
                }
                break;
            default:
                break;
        }

        bool any_non_zero = false;
        for (isize i = 1; i < 10; i += 1) {
            if (freqs[i] != 0) {
                any_non_zero = true;
                break;
            }
        }
        if (!any_non_zero) {
            if (freqs[0] > 0) {
                return "0";
            } else {
                return "";
            }
        }

        isize total_freqs = reduce(cbegin(freqs), cend(freqs), 0LL);
        auto res = string(total_freqs, ' ');
        isize idx = 0;
        for (isize i = 9 ; i >= 0; i -= 1) {
            const isize total_steps = freqs[i];
            for (isize steps = 0; steps < total_steps; steps += 1) {
                res[idx] = static_cast<char>(i + '0');
                idx += 1;
            }
        }
        return res;
    }
};
