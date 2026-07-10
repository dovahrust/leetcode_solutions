typedef ptrdiff_t isize;

class Solution {
public:
    static int arrayNesting(vector<int>& nums) {
        const isize len = std::ssize(nums);
        isize longest = 0;

        for (isize i = 0; i < len; i += 1) {
            isize curr_idx = i;
            isize count = 0;
            while (nums[curr_idx] >= 0) {
                const isize next_idx = nums[curr_idx];
                assert(next_idx < len);
                nums[curr_idx] = -nums[curr_idx] - 1;
                count += 1;
                curr_idx = next_idx;
            }
            longest = std::max(longest, count);
        }

        for (isize i = 0; i < len; i += 1) {
            nums[i] = -nums[i] - 1;
        }

        assert(longest <= numeric_limits<int>::max());

        return static_cast<int>(longest);
    }
};
