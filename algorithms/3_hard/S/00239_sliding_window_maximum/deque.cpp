typedef ptrdiff_t isize;

class Solution {
public:
    static vector<int> maxSlidingWindow(const vector<int>& nums, const int k_i32) {
        const isize k = k_i32;
        const isize len =  std::ssize(nums);
        assert(k > 0 && k <= len && len <= 100'000);
        auto res = vector<int>();
        res.reserve(len - k + 1);
        auto q = deque<pair<int, int>>();

        for (isize i = 0; i < len; i += 1) {
            const int num = nums[i];
            if (i >= k) {
                if (!q.empty() && q.front().first <= i - k) {
                    q.pop_front();
                }
            }

            while (!q.empty() && q.back().second <= num) {
                q.pop_back();
            }

            q.push_back(make_pair(static_cast<int>(i), num));

            if (i >= k - 1) {
                res.push_back(q.front().second);
            }
        }

        return res;
    }
};
