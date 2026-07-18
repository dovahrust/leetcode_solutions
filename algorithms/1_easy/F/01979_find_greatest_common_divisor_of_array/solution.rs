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

    pub fn find_gcd(nums: Vec<i32>) -> i32 {
        let mut min = i32::MAX;
        let mut max = i32::MIN;

        for num in nums.iter() {
            min = min.min(*num);
            max = max.max(*num);
        }

        Self::gcd(max, min)
    }
}
