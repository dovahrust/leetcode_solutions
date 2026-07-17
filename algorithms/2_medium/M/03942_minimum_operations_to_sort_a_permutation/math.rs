impl Solution {
    pub fn min_operations(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len > 0);
        if len == 1 { return 0; }
        let max_val = (len - 1) as i32;
        let min_val = 0_i32;

        for i in 1..len {
            let abs_diff = (nums[i] - nums[i - 1]).abs();
            if abs_diff != 1 {
                if (nums[i - 1] == min_val && nums[i] == max_val) || (nums[i] == min_val && nums[i - 1] == max_val) {
                    continue;
                }
                return -1;
            }
        }

        let mut min_idx = 0_usize;
        for i in 0..len {
            if nums[i] == 0 {
                min_idx = i;
                break;
            }
        }

        let next_idx = (min_idx + 1) % len;
        if nums[next_idx] == 1 {
            let with_rev_idx = (len - 1) - min_idx;
            // 1 rev to get ..1,0,n,..;
            // with_rev_idx shift to left to get 0,n,n-1,...,1;
            // 1 shift to left to get n,n-1,..,0;
            // 1 rev to get for 0,1,2,..n;
            let cost_with_rev = 1 + with_rev_idx + 1 + 1;
            // just simple shift to left;
            let direct = min_idx;
    
            return direct.min(cost_with_rev) as i32;
        }

        let with_rev_idx = (len - 1) - min_idx;
        // 1 rev to get ..n,0,1,..;
        // with_rev_idx shift to left to get 0,1,2,..,n;
        let cost_with_rev = with_rev_idx + 1;
        // min_idx shift to left to get 0,n,...;
        // 1 shift to left to get n,...,0;
        // 1 rev to get 0,..,n;
        let direct = min_idx + 1 + 1;

        direct.min(cost_with_rev) as i32
    }
}
