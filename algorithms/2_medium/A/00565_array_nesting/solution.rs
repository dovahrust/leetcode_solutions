impl Solution {
    pub fn array_nesting(mut nums: Vec<i32>) -> i32 {
        let len = nums.len();
        let mut longest = 0_usize;

        for i in 0..len {
            let mut curr_idx = i;
            let mut count = 0_usize;
            while nums[curr_idx] >= 0 {
                let next_idx = nums[curr_idx] as usize;
                assert!(next_idx < len);
                nums[curr_idx] = -nums[curr_idx] - 1;
                count += 1;
                curr_idx = next_idx;
            }
            longest = longest.max(count);
        }

        longest.try_into().unwrap()
    }
}
