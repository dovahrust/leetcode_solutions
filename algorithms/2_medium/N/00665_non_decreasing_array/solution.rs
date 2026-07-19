impl Solution {
    #[inline(always)]
    fn forward(nums: &[i32]) -> bool {
        let mut cnt = 0_i32;
        let mut max = i32::MIN;
        for &num in nums {
            max = max.max(num);
            if num < max {
                cnt += 1;
                if cnt >= 2 {
                    return false;
                } 
            }
        }
        true
    }

    #[inline(always)]
    fn backward(nums: &[i32]) -> bool {
        let mut cnt = 0_i32;
        let mut min = i32::MAX;
        for &num in nums.iter().rev() {
            min = min.min(num);
            if num > min {
                cnt += 1;
                if cnt >= 2 {
                    return false;
                } 
            }
        }
        true
    }

    pub fn check_possibility(nums: Vec<i32>) -> bool {
       Self::forward(&nums) || Self::backward(&nums)
    }
}
