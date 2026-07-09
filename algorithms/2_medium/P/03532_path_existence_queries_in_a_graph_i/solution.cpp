typedef ptrdiff_t isize;

class Solution {
public:
    vector<bool> pathExistenceQueries(const int n, const vector<int>& nums, const int max_diff, const vector<vector<int>>& queries) {
        const isize len = std::ssize(nums);
        auto ranks = vector<int>(len);
        ranks[0] = 0;

        for (int i = 1; i < len; i += 1) {
            assert(nums[i] >= nums[i - 1]);
            if (nums[i] - nums[i - 1] <= max_diff) {
                ranks[i] = ranks[i - 1];
            } else {
                ranks[i] = ranks[i - 1] + 1;
            }
        }

        const isize queries_len = std::ssize(queries);
        auto res = vector<bool>(queries_len);

        for (int i = 0; i < queries_len; i += 1) {
            const auto& q = queries[i];
            assert(std::ssize(q) == 2);
            const int lo = std::min(q[0], q[1]);
            const int hi = std::max(q[0], q[1]);
            assert(lo >= 0 && hi >=0 && lo < len && hi < len);
            res[i] = (ranks[lo] == ranks[hi]);
        }

        return res;
    }
};
