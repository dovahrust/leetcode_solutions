use std::collections::VecDeque;

impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        assert!(k > 0 && (k as usize) <= nums.len() && nums.len() <= 100_000);
        let k = k as usize;
        let res_len = nums.len() - k + 1;
        let mut res = Vec::with_capacity(res_len);
        let mut q: VecDeque<(u32, i32)> =  VecDeque::with_capacity(k);

        for (i, num) in nums.into_iter().enumerate() {
            if i >= k {
                if let Some((idx_u32, _)) = q.front() && (*idx_u32  as usize) <= (i - k) {
                    q.pop_front();
                }
            }

            while let Some((_, val)) = q.back() && *val <= num {
                q.pop_back();
            }

            q.push_back((i as u32, num));

            if i >= k - 1 {
                res.push(q.front().unwrap().1)
            }
        }

        res
    }
}
