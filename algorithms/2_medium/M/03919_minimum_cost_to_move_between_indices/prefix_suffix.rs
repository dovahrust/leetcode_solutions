impl Solution {
    pub fn min_cost(nums: Vec<i32>, queries: Vec<Vec<i32>>) -> Vec<i32> {
        let len = nums.len();
        assert!(len >= 2);
        let mut buff = vec![0_i32; 2 * len];
        let (mut prefix, mut suffix) = buff.split_at_mut(len);
        let mut res = vec![0_i32; queries.len()];

        prefix[1] = 1;
        for i in 1..(len - 1) {
            debug_assert!(nums[i - 1] < nums[i] && nums[i] < nums[i + 1]);
            let diff_l = (nums[i] - nums[i - 1]).abs();
            let diff_r = (nums[i + 1] - nums[i]).abs();

            if diff_l > diff_r {
                prefix[i + 1] = 1 + prefix[i];
            } else {
                prefix[i + 1] = diff_r + prefix[i];
            }
        }

        suffix[len - 2] = 1;
        for i in (1..(len - 1)).rev() {
            let diff_l = (nums[i] - nums[i - 1]).abs();
            let diff_r = (nums[i + 1] - nums[i]).abs();

            if diff_l <= diff_r {
                suffix[i - 1] = 1 + suffix[i];
            } else {
                suffix[i - 1] = diff_l + suffix[i];
            }
        }

        for (i, q) in queries.into_iter().enumerate() {
            assert!(q.len() == 2);
            let (l, r) = (q[0], q[1]);
            assert!(l >= 0 && r >= 0 && (l as usize) < len && (r as usize) < len);

            if l <= r {
                res[i] = prefix[r as usize] - prefix[l as usize];
            } else {
                res[i] = suffix[r as usize] - suffix[l as usize];
            }
        }

        res
    }
}
