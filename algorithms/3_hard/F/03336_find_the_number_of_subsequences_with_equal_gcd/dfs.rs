impl Solution {
    const MOD: i64 = 1_000_000_007;

    #[inline(always)]
    fn gcd(mut a: i32, mut b: i32) -> i32 {
        while b != 0 {
            let t = b;
            b = a % b;
            a = t;
        }
        a
    }

    fn dfs(nums: &[i32], nums_idx: usize, g1: i32, g2: i32, memo: &mut [i32], memo_rows: usize , memo_cols: usize) -> i64 {
        let nums_len = nums.len();
        if nums_idx == nums_len {
            if g1 != 0 && g1 == g2 {
                return 1;
            } else {
                return 0;
            }
        }
        let memo_idx = nums_idx * (memo_rows * memo_cols) + (g1 as usize) * memo_cols + (g2 as usize);
        if memo[memo_idx] != -1 {
            return memo[memo_idx] as i64;
        }
        let res = (Self::dfs(nums, nums_idx + 1, Self::gcd(g1, nums[nums_idx]), g2, memo, memo_rows, memo_cols) +
                  Self::dfs(nums, nums_idx + 1, g1, Self::gcd(g2, nums[nums_idx]), memo, memo_rows, memo_cols) +
                  Self::dfs(nums, nums_idx + 1, g1, g2, memo, memo_rows, memo_cols)) % Self::MOD;
        memo[memo_idx] = res as i32;
        res        
    }

    pub fn subsequence_pair_count(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len >= 1 && len <= 200 && nums.iter().all(|num| *num >= 1 && *num <= 200));
        if len == 1 { return 0; }
        let max = *nums.iter().max().unwrap();
        let memo_cols = (max + 1) as usize;
        let memo_rows = memo_cols;
        let memo_height = len;
        let mut memo = vec![-1_i32; (memo_rows * memo_cols * memo_height)];
        let (g1, g2) = (0, 0);
        
        ( Self::dfs(&nums, 0, g1, g2, &mut memo, memo_rows, memo_cols) % Self::MOD ) as i32
    }
}
