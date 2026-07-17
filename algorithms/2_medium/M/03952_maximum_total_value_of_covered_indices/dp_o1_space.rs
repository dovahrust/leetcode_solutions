impl Solution {
    pub fn max_total(nums: Vec<i32>, s: String) -> i64 {
        let len = nums.len();
        let bytes = s.as_bytes();
        assert!(len == bytes.len() && len > 0);
        let (mut prev_prev, mut prev) = (0_i64, 0_i64);
        if bytes[0] == b'1' {
            prev = nums[0] as i64;
        }

        for i in 1..len {
            if bytes[i] == b'1' {
                let curr = (prev_prev + nums[i - 1] as i64).max(prev + nums[i] as i64);
                let new_prev = prev.max(prev_prev + nums[i - 1] as i64);
                
                (prev_prev, prev) = (new_prev, curr);
            } else {
                prev_prev = prev;
            };
        }

        prev
    }
}
