impl Solution {
    pub fn can_cross(stones: Vec<i32>) -> bool {
        let len = stones.len();
        assert!(len >= 2 && len <= 2000 && stones[0] == 0);
        for i in 1..len {
            assert!(stones[i] > stones[i - 1]);
            let diff_adj = (stones[i] - stones[i - 1]) as usize;
            if diff_adj > i {
                return false;
            }
        }

        let dp_cols = len + 1;
        let mut dp = vec![false; len * dp_cols];
        dp[0] = true;

        for i in 1..len {
            let curr = stones[i];
            let curr_base = i * dp_cols;
            for j in (0..i).rev() {
                let prev = stones[j];
                let prev_base = j * dp_cols;
                let diff = (curr - prev) as usize;

                if diff > i {
                    break;
                }

                if dp[prev_base + diff - 1] || dp[prev_base + diff] || dp[prev_base + diff + 1] {
                    if i == len - 1 {
                        return true;
                    }

                    dp[curr_base + diff] = true;
                }
            }
        }

        false
    }
}
