typedef ptrdiff_t isize;

class Solution {
public:
    static long long makeSimilar(vector<int>& nums, vector<int>& target) {
        assert(std::ssize(nums) == std::ssize(target));
        ranges::sort(nums);
        ranges::sort(target);

        const isize len = std::ssize(nums);
        isize idx_odd = 0;
        isize idx_even = 0;
        isize idx_target = 0;
        int64_t cnt = 0;

        while (true) {
            while (idx_odd < len && (nums[idx_odd] & 1) == 0) {
                idx_odd += 1;
            }
            while (idx_even < len && (nums[idx_even] & 1) == 1) {
                idx_even += 1;
            }

            if (idx_odd == len && idx_even == len) {
                break;
            }

            if ((target[idx_target] & 1) == 1) {
                assert(idx_odd < len && "invalid input: missing odd number");
                cnt += std::abs(target[idx_target] - nums[idx_odd]) / 2;
                idx_odd += 1;
            } else {
                assert(idx_even < len && "invalid input: missing even number");
                cnt += std::abs(target[idx_target] - nums[idx_even]) / 2;
                idx_even += 1;
            }
            idx_target += 1;
        }

        return cnt / 2;
    }
};
