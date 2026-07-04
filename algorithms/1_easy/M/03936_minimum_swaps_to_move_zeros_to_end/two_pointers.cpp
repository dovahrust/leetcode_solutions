typedef ptrdiff_t isize;

class Solution {
public:
    static int minimumSwaps(const vector<int>& nums) {
        int cnt = 0;
        isize lo = 0;
        isize hi = std::ssize(nums) - 1;

        while (true) {
            while (lo < hi && nums[hi] == 0) {
                hi -= 1;
            }

            while (lo < hi && nums[lo] != 0) {
                lo += 1;
            }

            if (lo >= hi) {
                break;
            }

            cnt += 1;
            lo += 1;
            hi -= 1;
        }

        return cnt;
    }
};
