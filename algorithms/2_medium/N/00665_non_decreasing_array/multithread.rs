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
        let slice = nums.as_slice();

        let (forward_ok, backward_ok) = std::thread::scope(|s| {
            let t1 = s.spawn(|| Self::forward(slice));
            let t2 = s.spawn(|| Self::backward(slice));
            (t1.join().unwrap(), t2.join().unwrap())
        });

       forward_ok || backward_ok
    }
}
