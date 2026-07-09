impl Solution {
    pub fn path_existence_queries(n: i32, nums: Vec<i32>, max_diff: i32, queries: Vec<Vec<i32>>) -> Vec<bool> {
        let len = nums.len();
        assert!(len > 0);
        let mut ranks: Vec<i32> = Vec::with_capacity(len);
        unsafe { ranks.set_len(len); }
        ranks[0] = 0;
        for i in 1..len {
            debug_assert!(nums[i] >= nums[i - 1]);
            if nums[i] - nums[i - 1] <= max_diff {
                ranks[i] = ranks[i - 1];
            } else {
                ranks[i] = ranks[i - 1] + 1;
            }
        }

        let mut res = Vec::with_capacity(queries.len());
        unsafe { res.set_len(queries.len()); }

        for (i, q) in queries.into_iter().enumerate() {
            let lo = q[0].min(q[1]);
            let hi = q[0].max(q[1]);
            debug_assert!(lo >= 0 && hi >=0 && (lo as usize) < len && (hi as usize) < len);
            res[i] = (ranks[lo as usize] == ranks[hi as usize]);
        }

        res
    }
}
