impl Solution {
    #[inline(always)]
    fn init_max(nums: &[i32], k: i64) -> Vec<(i64, i64, i64)> {
        let len = nums.len();
        let mut max = vec![(0_i64, 0_i64, 0_i64); len + 1];
        let (mut by, mut by_mul, mut by_div) = (0_i64, 0_i64, 0_i64);
        for i in (0..len).rev() {
            let num = nums[i] as i64;
            by_mul = (by_mul.max(by) + num * k).max(0);
            by_div = (by_div.max(by) + num / k).max(0);
            by = (by + num).max(0);
            max[i] = (by, by_mul, by_div);
        }

        max
    }

    pub fn max_subarray_sum(nums: Vec<i32>, k: i32) -> i64 {
        assert!(k >= 1);
        let k = k as i64;
        let len = nums.len();
        let max = Self::init_max(&nums, k);
        let (mut by_l, mut by_mul_l, mut by_div_l) = (0_i64, 0_i64, 0_i64);
        let mut res = i64::MIN;

        for (i, num_i32) in nums.into_iter().enumerate() {
            let (by_r, by_mul_r, by_div_r) = max[i + 1];
            let num = num_i32 as i64;
            by_mul_l = by_mul_l.max(0) + num * k;
            by_div_l = by_div_l.max(0) + num / k;
            by_l = by_l.max(0) + num;
            res = res.max(by_mul_l + by_r).max(by_div_l + by_r).max(by_l + by_mul_r).max(by_l + by_div_r);
        }
        
        res
    }
}
