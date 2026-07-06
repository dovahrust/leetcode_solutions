impl Solution {
    pub fn min_patches(nums: Vec<i32>, n: i32) -> i32 {
        let n = n as i64;
        let len = nums.len();
        let mut idx = 0_usize;
        let mut miss = 1_i64;
        let mut patches = 0_i32;

        while miss <= n {
            if idx < len && miss >= nums[idx] as i64 {
                miss += nums[idx] as i64;
                idx += 1;
            } else {
                miss += miss;
                patches += 1;
            }
        }

        patches
    }
}
