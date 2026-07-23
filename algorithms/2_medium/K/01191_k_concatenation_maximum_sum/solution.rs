impl Solution {
    const MOD: i64 = 1_000_000_007;

    pub fn k_concatenation_max_sum(arr: Vec<i32>, k: i32) -> i32 {
        assert!(k >= 1 && arr.len() > 0);
        let k = k as i64;
        let mut max_sub = 0_i64;
        let mut curr = 0_i64;
        for &a in &arr {
            curr += a as i64;
            max_sub = max_sub.max(curr);
            if curr < 0 {
                curr = 0;
            }
        }

        if k == 1 || max_sub == 0 {
            return (max_sub % Self::MOD) as i32;
        }

        let sum = arr.iter().map(|x| *x as i64).sum::<i64>().max(0_i64);

        let mut max_l = 0_i64;
        let mut curr = 0_i64;
        for &a in &arr {
            curr += a as i64;
            max_l = max_l.max(curr);
        }

        let mut max_r = 0_i64;
        let mut curr = 0_i64;
        for &a in arr.iter().rev() {
            curr += a as i64;
            max_r = max_r.max(curr);
        }

        ((sum * (k - 2) + max_l + max_r).max(max_sub) % Self::MOD) as i32
    }
}
