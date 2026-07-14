impl Solution {
    pub fn max_valid_pair_sum(nums: Vec<i32>, k: i32) -> i32 {
        assert!(k > 0 && (k as usize) < nums.len());
        let k = k as usize;
        let len = nums.len();

        let mut max_lo = i32::MIN;
        let mut res = i32::MIN;
        let end = len - k;
        for i in 0..end {
            max_lo = max_lo.max(nums[i]);
            res = res.max(max_lo + nums[i + k]);
        }

        res
    }
}
