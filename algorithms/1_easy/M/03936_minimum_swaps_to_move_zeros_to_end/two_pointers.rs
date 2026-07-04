impl Solution {
    pub fn minimum_swaps(nums: Vec<i32>) -> i32 {
        if nums.is_empty() { return 0; }
        let mut cnt = 0_i32;
        let mut lo = 0_usize;
        let mut hi = nums.len() - 1;

        loop {
            while lo < hi && nums[hi] == 0 {
                hi -= 1;
            }

            while lo < hi && nums[lo] != 0 {
                lo += 1;
            }

            if lo >= hi {
                break;
            }

            cnt += 1;
            lo += 1;
            hi -= 1;
        }

        cnt
    }
}
