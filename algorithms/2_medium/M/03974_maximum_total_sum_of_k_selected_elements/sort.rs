impl Solution {
    pub fn max_sum(mut nums: Vec<i32>, k: i32, mul: i32) -> i64 {
        assert!(nums.len() > 0 && k >= 1 && (k as usize) <= nums.len() && mul >= 1);
        let k = k as usize;
        let mut mul = mul as i64;
        let len = nums.len();
        nums.sort_unstable();
        assert!(nums[0] >= 1);
        let mut sum = 0_i64;

        for i in ((len - k)..len).rev() {
            if mul > 0 {
                sum += mul * (nums[i] as i64);
                mul -= 1;
            } else {
                sum += nums[i] as i64;
            }
        }

        sum
    }
}
