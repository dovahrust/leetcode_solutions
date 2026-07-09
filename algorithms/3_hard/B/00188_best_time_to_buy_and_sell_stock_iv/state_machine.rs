impl Solution {
    pub fn max_profit(k: i32, prices: Vec<i32>) -> i32 {
        let len = prices.len();
        if k <= 0 || len == 0 { return 0; }
        let k = k as usize;
        let mut buff: Vec<i32> = Vec::with_capacity(2 * (k + 1));
        unsafe { buff.set_len(2 * (k + 1)); }
        let (dp, hold) = buff.split_at_mut(k + 1);
        dp.iter_mut().for_each(|x| *x = 0);
        hold.iter_mut().for_each(|x| *x = i32::MIN);

        for p in prices {
            for i in (1..=k).rev() {
                dp[i] = dp[i].max(hold[i] + p);
                hold[i] = hold[i].max(dp[i - 1] - p);
            }
        }

        dp[k]
    }
}
