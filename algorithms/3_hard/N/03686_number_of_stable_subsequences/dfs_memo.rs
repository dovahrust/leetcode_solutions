impl Solution {
    const MOD: i64 = 1_000_000_007;

    fn dfs(nums: &[i32], idx: usize, mut cnt_odd: u8, mut cnt_even: u8, memo: &mut [i32]) -> i32 {
        let len = nums.len();

        if idx == len {
            return 0;
        }

        let memo_idx = idx + match (cnt_odd, cnt_even) {
            (0, 0) => 0,
            (0, 1) => len,
            (0, 2) => 2 * len,
            (1, 0) => 3 * len,
            (2, 0) => 4 * len,
            _ => unreachable!()
        };

        if memo[memo_idx] != -1 {
            return memo[memo_idx];
        }

        let skip = Self::dfs(nums, idx + 1, cnt_odd, cnt_even, memo) as i64;

        let keep = {
            if (nums[idx] & 1) == 1 { 
                cnt_odd += 1;
                cnt_even = 0;
            } else {
                cnt_even += 1;
                cnt_odd = 0;
            }

            if cnt_odd < 3 && cnt_even < 3 {
                1 + Self::dfs(nums, idx + 1, cnt_odd, cnt_even, memo) as i64
            } else {
                0
            }
        };

        let res = ((skip + keep) % Self::MOD) as i32;
        memo[memo_idx] = res;
        res
    }

    pub fn count_stable_subsequences(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len > 0);
        let mut memo = vec![-1_i32; 5 * len];

        Self::dfs(&nums, 0, 0, 0, &mut memo)
    }
}
