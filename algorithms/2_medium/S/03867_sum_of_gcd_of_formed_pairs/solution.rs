impl Solution {
    #[inline(always)]
    fn gcd(mut a: i32, mut b: i32) -> i32 {
        assert!(a >= 0 && b >= 0);
        while b != 0 {
            let temp = b;
            b = a % b;
            a = temp;
        }
        a
    }

    pub fn gcd_sum(mut nums: Vec<i32>) -> i64 {
        assert!(nums.len() > 0);
        let mut max = 0;

        for num in nums.iter_mut() {
            max = max.max(*num);
            *num = Self::gcd(max, *num);
        }

        nums.sort_unstable();

        let (mut lo, mut hi) = (0_usize, nums.len() - 1);
        let mut sum = 0_i64;

        while lo < hi {
            sum += Self::gcd(nums[lo], nums[hi]) as i64;
            lo += 1;
            hi -= 1;
        }

        sum
    }
}
