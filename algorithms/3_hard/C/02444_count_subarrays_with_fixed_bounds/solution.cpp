typedef ptrdiff_t isize;

class Solution {
public:
    long long countSubarrays(const vector<int>& nums, int min_k, int max_k) {
        const isize len = std::ssize(nums);
        int64_t cnt = 0;
        isize begin = 0;
        isize min_idx = 0;
        isize max_idx = 0;

        for (isize i = 0; i < len; i += 1) {
            const int num = nums[i];

            if (num > max_k || num < min_k) {
                min_idx = i + 1;
                max_idx = i + 1;
                begin = i + 1;
            } else {
                if (nums[min_idx] >= num) {
                    min_idx = i;
                }
                if (nums[max_idx] <= num) {
                    max_idx = i;
                }

                if (nums[max_idx] == max_k && nums[min_idx] == min_k) {
                    cnt += static_cast<int64_t>(std::min(min_idx, max_idx) - begin + 1);
                }
            }
        }

        return cnt;
    }
};
