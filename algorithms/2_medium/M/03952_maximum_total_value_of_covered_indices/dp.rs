impl Solution {
    pub fn max_total(nums: Vec<i32>, s: String) -> i64 {
        let len = nums.len();
        let bytes = s.as_bytes();
        assert!(len == bytes.len() && len > 0);
        let mut dp = vec![0_i64; len + 2];
        if bytes[0] == b'1' {
            dp[2] = nums[0] as i64;
        }

        for i in 1..len {
            if bytes[i] == b'1' {
                dp[i + 2] = (dp[i + 1] + nums[i] as i64).max(dp[i] + nums[i - 1] as i64);
                dp[i + 1] = dp[i + 1].max(dp[i] + nums[i - 1] as i64);
            } else {
                dp[i + 2] = dp[i + 1];
            }
        }

        dp[len + 1]
    }
}
