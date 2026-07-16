impl Solution {
    pub fn is_middle_element_unique(nums: Vec<i32>) -> bool {
        assert!(nums.len() > 0 && (nums.len() & 1) == 1);
        let mid_idx = nums.len() / 2;
        let mid_val = nums[mid_idx];

        for i in 0..mid_idx {
            if nums[i] == mid_val || nums[i + mid_idx + 1] == mid_val {
                return false;
            }
        }

        true
    }
}
