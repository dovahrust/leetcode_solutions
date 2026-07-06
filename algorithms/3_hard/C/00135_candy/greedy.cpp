typedef ptrdiff_t isize;

class Solution {
public:
    static int candy(const vector<int>& ratings) {
        assert(std::ssize(ratings) <= 2 * 10'000);
        const isize len = std::ssize(ratings);
        auto vec = vector<int>(len, 1);
        int cnt = 0;

        for (isize i = 1; i < len; i +=1) {
            if (ratings[i - 1] < ratings[i]) {
                vec[i] = vec[i - 1] + 1;
            }
        }

        for (isize i = len - 1; i > 0; i -=1) {
            if (ratings[i - 1] > ratings[i]) {
                vec[i - 1] = std::max(vec[i - 1], vec[i] + 1);
            }
            cnt += vec[i - 1];
        }
        cnt += vec[len - 1];

        return cnt;
    }
};
