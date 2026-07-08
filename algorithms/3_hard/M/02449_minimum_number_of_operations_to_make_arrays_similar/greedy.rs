impl Solution {
    pub fn make_similar(mut nums: Vec<i32>, mut target: Vec<i32>) -> i64 {
        assert!(nums.len() == target.len());
        nums.sort_unstable();
        target.sort_unstable();

        let len = nums.len();
        let mut idx_odd = 0_usize;
        let mut idx_even = 0_usize;
        let mut idx_target = 0_usize;
        let mut cnt = 0_i64;

        loop {
            while idx_odd < len && (nums[idx_odd] & 1) == 0 {
                idx_odd += 1;
            }
            while idx_even < len && (nums[idx_even] & 1) == 1 {
                idx_even += 1;
            }

            if idx_odd == len && idx_even == len {
                break;
            }

            if (target[idx_target] & 1) == 1 {
                let val = *nums.get(idx_odd).expect("invalid input: missing odd number");
                cnt += ((target[idx_target] - val) / 2).abs() as i64;
                idx_odd += 1;
            } else {
                let val = *nums.get(idx_even).expect("invalid input: missing even number");
                cnt += ((target[idx_target] - val) / 2).abs() as i64;
                idx_even += 1;
            }
            idx_target += 1;
        }

        cnt / 2
    }
}
