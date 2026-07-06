typedef ptrdiff_t isize;

class Solution {
public:
    static int minPatches(const vector<int>& nums, const int n_i32) {
        const int64_t n = n_i32;
        const isize len = std::ssize(nums);
        isize idx = 0;
        int64_t miss = 1;
        int patches = 0;

        while (miss <= n) {
            if (idx < len && miss >= nums[idx]) {
                miss += nums[idx];
                idx += 1;
            } else {
                miss += miss;
                patches += 1;
            }
        }

        return patches;
    }
};
