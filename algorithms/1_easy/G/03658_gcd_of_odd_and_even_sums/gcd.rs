impl Solution {
    #[inline(always)]
    fn gcd(mut a: i32, mut b: i32) -> i32 {
        while b != 0 {
            let temp = b;
            b = a % b;
            a = temp;
        }
        a
    }

    pub fn gcd_of_odd_even_sums(mut n: i32) -> i32 {
        assert!(n <= 1000 && n >= 1);
        let sum_n_odd_n_even = (n * 2) * (n * 2 + 1) / 2;
        let sum_half_n_odd_half_n_even = (n * (n + 1)) / 2;
        let sum_n_even = 2 * sum_half_n_odd_half_n_even;
        let sum_n_odd = sum_n_odd_n_even - sum_n_even;

        Self::gcd(sum_n_even, sum_n_odd)
    }
}
