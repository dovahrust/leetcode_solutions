impl Solution {
    const MOD: i64 = 1_000_000_007;

    pub fn minimum_cost(nums: Vec<i32>, k: i32) -> i32 {
        let k = k as i64;
        let mut sum = nums.iter().map(|x| *x as i64).sum::<i64>();
        let ops = (sum - 1) / k;
        ((ops % Self::MOD) * ((ops + 1) % Self::MOD) / 2 % Self::MOD) as i32
    }
}
