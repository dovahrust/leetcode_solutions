impl Solution {
    pub fn sum_and_multiply(n: i32) -> i64 {
        assert!(n >= 0);
        let mut sum = 0_i64;
        let mut res = 0_i64;
        let mut p = 1_i32;

        while (n / p >= 10) {
            p *= 10;
        }

        while p > 0 {
            let dig = ((n / p) % 10) as i64;
            p /= 10;

            if dig > 0 {
                res *= 10;
                res += dig;
                sum += dig;
            }
        }

        res * sum
    }
}
