impl Solution {
    pub fn count_valid_subarrays(nums: Vec<i32>, x: i32) -> i32 {
        assert!(x >= 1 && x <= 9);
        let x = x as i64;
        let len = nums.len();
        let mut cnt = 0;

        for i in 0..len {
            let mut sum = 0_i64;
            for j in i..len {
                sum += nums[j] as i64;
                let lowest_dig = sum % 10;
                if lowest_dig == x {
                    let mut temp = sum;
                    while temp >= 10 {
                        temp /= 10;
                    }
                    let highest_dig = temp;
                    if highest_dig == x {
                        cnt += 1;
                    }
                }
            }
        }

        cnt
    }
}
