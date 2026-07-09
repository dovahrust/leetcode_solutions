typedef ptrdiff_t isize;

class Solution {
public:
    static int findMin(const vector<int>& nums) {
        const isize len = std::ssize(nums);
        assert(len > 0);
        isize lo = 0;
        isize hi = len - 1;

        while (lo < hi) {
            const isize mid = lo + (hi - lo) / 2;
            if (nums[mid] < nums[hi]) {
                hi = mid;
            } else if (nums[mid] == nums[hi]) {
                hi -= 1;
            } else {
                lo = mid + 1;
            }
        }

        return nums[lo];
    }
};
