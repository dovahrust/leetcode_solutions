impl Solution {
    #[inline(always)]
    fn is_ok(grid: &[Vec<i32>], lo: usize, hi: usize, limit: i32) -> bool {
        let len = grid.len();
        for i in 0..len {
            if (grid[i][hi] - grid[i][lo]).abs() > limit {
                return false;
            }
        }
        true
    }

    pub fn max_consistent_columns(grid: Vec<Vec<i32>>, limit: i32) -> i32 {
        assert!(grid.len() >= 1 && grid[0].len() >= 1 && grid[0].len() <= 250);
        let rows = grid.len();
        let cols = grid[0].len();
        let mut dp = vec![1_i16; cols];
        for i in 0..cols {
            for j in 0..i {
                if Self::is_ok(&grid, j, i, limit) {
                    dp[i] = dp[i].max(1 + dp[j]);
                }
            }
        }

        dp.into_iter().max().unwrap() as i32
    }
}
