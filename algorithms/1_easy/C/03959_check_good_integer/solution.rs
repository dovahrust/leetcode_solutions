impl Solution {
    pub fn check_good_integer(mut n: i32) -> bool {
        let mut sum_square_dig = 0_i32;
        let mut sum_dig = 0_i32;

        while n > 0 {
            let dig = n % 10;
            n /= 10;
            sum_square_dig += dig * dig;
            sum_dig += dig;

            if sum_square_dig - sum_dig >= 50 {
                return true;
            }
        }

        false
    }
}
