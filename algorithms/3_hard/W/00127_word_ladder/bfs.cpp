typedef ptrdiff_t isize;

const int16_t inf = numeric_limits<int16_t>::max() / 2;

class Solution {
    static inline int calc_diff(const string_view s1, const string_view s2) {
        int diff = 0;
        const isize n = std::ssize(s1);
        for (isize i = 0; i < n; i += 1) {
            if (s1[i] != s2[i]) {
                diff += 1;
            }
        }
        return diff;
    }

public:
    static int ladderLength(const string& begin_word, const string& end_word, const vector<string>& word_list) {
        const isize word_list_len = std::ssize(word_list);
        assert(word_list_len <= 5000);
        assert(begin_word != end_word);
        bool end_word_exist = false;
        for (isize i = 0; i < word_list_len; i += 1) {
            if (calc_diff(word_list[i], end_word) == 0) {
                end_word_exist = true;
                break;
            }
        }
        if (!end_word_exist) { return 0; }

        auto buff = vector<int16_t>(2 * word_list_len, inf);
        auto avaiables = span<int16_t>(&buff[0], word_list_len);
        auto costs = span<int16_t>(&buff[word_list_len], word_list_len);
        for (isize i = 0; i < word_list_len; i += 1) { avaiables[i] = static_cast<int16_t>(i); }
        isize hi = word_list_len;
        isize lo = 0;
        auto q = deque<int16_t>();

        while (lo < hi) {
            const int diff = calc_diff(begin_word, word_list[avaiables[lo]]);
            if (diff == 1) {
                costs[avaiables[lo]] = 2;
                q.push_back(avaiables[lo]);
                hi -= 1;
                avaiables[lo] = avaiables[hi];
            } else if (diff == 0) {
                costs[avaiables[lo]] = 0;
                hi -= 1;
                avaiables[lo] = avaiables[hi];
            } else {
                lo += 1;
            }
        }

        while (!q.empty()) {
            const isize i = q.front();
            q.pop_front();
            const int curr_cost = costs[i];
            isize lo = 0;
            while (lo < hi) {
                const int diff = calc_diff(word_list[i], word_list[avaiables[lo]]);
                if (diff == 1) {
                    costs[avaiables[lo]] = curr_cost + 1;
                    q.push_back(avaiables[lo]);
                    hi -= 1;
                    avaiables[lo] = avaiables[hi];
                } else {
                    lo += 1;
                }
            }
        }

        for (isize i = 0; i < word_list_len; i += 1) {
            if (calc_diff(end_word, word_list[i]) == 0) {
                if (costs[i] == inf) {
                    return 0;
                } else {
                    return costs[i];
                }
            }
        }

        cerr << "unreachable!\n";
        exit(0);
    }
};
