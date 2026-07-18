impl Solution {
    pub fn compare_bitonic_sums(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len >= 3);
        let (mut lo, mut hi) = (0_usize, len - 1);
        let (mut sum_l, mut sum_r) = (0_i64, 0_i64);

        while lo < hi && nums[hi - 1] >= nums[hi] {
            sum_r += nums[hi] as i64;
            hi -= 1;
        }

        if hi == 0 || hi == len - 1 {
            unreachable!("invalid input, arr is not bitonic");
        }

        while lo < hi && nums[lo] <= nums[lo + 1] {
            sum_l += nums[lo] as i64;
            lo += 1;
        }

        if lo != hi {
            unreachable!("invalid input, arr is not bitonic");
        }

        match sum_r.cmp(&sum_l) {
            std::cmp::Ordering::Less => 0,
            std::cmp::Ordering::Greater => 1,
            std::cmp::Ordering::Equal => -1
        }
    }
}
