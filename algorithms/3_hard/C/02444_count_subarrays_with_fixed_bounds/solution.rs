impl Solution {
    pub fn count_subarrays(nums: Vec<i32>, min_k: i32, max_k: i32) -> i64 {
        let len = nums.len();
        let mut cnt = 0_i64;
        let mut begin = 0_usize;
        let mut min_idx = 0_usize;
        let mut max_idx = 0_usize;

        for i in 0..len {
            let num = nums[i];

            if num > max_k || num < min_k {
                min_idx = i + 1;
                max_idx = i + 1;
                begin = i + 1;
            } else {
                if nums[min_idx] >= num {
                    min_idx = i;
                }
                if nums[max_idx] <= num {
                    max_idx = i;
                }

                if nums[max_idx] == max_k && nums[min_idx] == min_k {
                    cnt += (std::cmp::min(min_idx, max_idx) - begin + 1) as i64;
                }
            }
        }

        cnt
    }
}
