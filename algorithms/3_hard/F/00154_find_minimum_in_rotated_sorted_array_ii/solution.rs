impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len > 0);
        let mut lo = 0_usize;
        let mut hi = len - 1;

        while lo < hi {
            let mid = lo + (hi - lo) / 2;
            if nums[mid] < nums[hi] {
                hi = mid;
            } else if nums[mid] == nums[hi] {
                hi -= 1;
            } else {
                lo = mid + 1;
            }
        }

        nums[lo]
    }
}
