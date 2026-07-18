impl Solution {
    pub fn concat_with_reverse(nums: Vec<i32>) -> Vec<i32> {
        let len = nums.len();
        assert!(len > 0);
        let mut res = Vec::with_capacity(2 * len);
        unsafe { res.set_len(2 * len); }
        for i in 0..len {
            res[i] = nums[i];
            res[2 * len - 1 - i] = nums[i];
        }
        res
    }
}
