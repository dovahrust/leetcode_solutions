impl Solution {
    const MOD: i32 = 1_000_000_007;

    #[inline(always)]
    fn gcd(mut a: i32, mut b: i32) -> i32 {
        while b != 0 {
            let t = b;
            b = a % b;
            a = t;
        }
        a
    }

    pub fn subsequence_pair_count(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        assert!(len >= 1 && len <= 200 && nums.iter().all(|num| *num >= 1 && *num <= 200));
        if len == 1 { return 0; }
        let max = *nums.iter().max().unwrap();
        let rows = (max + 1) as usize;
        let cols = (max + 1) as usize;
        let mut buff = vec![0_i32; 2 * rows * cols];
        let (mut curr, mut next) = buff.split_at_mut(rows * cols);
        curr[0] = 1;    

        for num in nums {
            for (i, &cnt) in curr.iter().enumerate() {
                next[i] = curr[i];
            }
            for g1 in 0..=max {
                for g2 in 0..=max {
                    let cnt = curr[(g1 as usize) * cols  + (g2 as usize)];
                    if cnt == 0 { continue; }

                    let idx_g1_pick = (Self::gcd(g1, num) as usize) * cols + (g2 as usize);
                    let idx_g2_pick = (g1 as usize) * cols + (Self::gcd(g2, num) as usize);

                    next[idx_g1_pick] = (next[idx_g1_pick] + cnt) % Self::MOD;
                    next[idx_g2_pick] = (next[idx_g2_pick] + cnt) % Self::MOD;
                }
            }
            (curr, next) = (next, curr);
        }
        
        let mut res = 0_i32;

        for i in 1..=max {
            res = (res + curr[(i as usize) * cols + i as usize]) % Self::MOD;
        }

        res
    }
}
