impl Solution {
    const MOD: i32 = 1_000_000_007;

    fn dfs(n: i32, k: i32, target: i32, memo: &mut[i32], memo_cols: usize) -> i32 {
        if target < 0 || n < 0 {
            return 0;
        }
        if n == 0 {
            return if target == 0 { 1 } else { 0 };
        }

        let memo_idx = (n as usize) * memo_cols + target as usize;
        if memo[memo_idx] != - 1 {
            return memo[memo_idx];
        }

        let mut res = 0_i32;
        for i in 1..=k {
            res = (res + Self::dfs(n - 1, k, target - i, memo, memo_cols)) % Self::MOD;
        }

        memo[memo_idx] = res;
        res
    }
    pub fn num_rolls_to_target(n: i32, k: i32, target: i32) -> i32 {
        assert!(n >= 1 && n <= 30 && k >= 1 && k <= 30 && target >= 1 && target <= 1000);
        let memo_cols = (target + 1) as usize;
        let mut memo = vec![-1_i32; (1 + n as usize) * memo_cols];

        Self::dfs(n, k, target, &mut memo, memo_cols)
    }
}
