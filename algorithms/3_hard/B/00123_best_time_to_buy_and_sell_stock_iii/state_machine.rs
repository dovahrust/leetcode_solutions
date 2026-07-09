impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        const k: usize = 2;
        let mut hold = [i32::MIN; k + 1];
        let mut dp = [0_i32; k + 1];

        for p in prices {
            for i in (1..=k).rev() {
                dp[i] = dp[i].max(hold[i] + p);
                hold[i] = hold[i].max(dp[i - 1] - p);
            }
        }

        dp[k]
    }
}
