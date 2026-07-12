impl Solution {
    pub fn circular_array_loop(mut nums: Vec<i32>) -> bool {
        let len  = nums.len();
        let mut seen = i32::MAX;

        for i in 0..len {
            seen -= 1;

            if nums[i] < seen {
                let mut prev_is_pos = nums[i] >= 0;
                let mut prev_idx = i;
                let mut curr_idx = i;

                while nums[curr_idx] < seen {
                    let curr_is_pos = nums[curr_idx] >= 0;
                    if curr_is_pos != prev_is_pos {
                        seen -= 1;
                    }
                    prev_is_pos = curr_is_pos;

                    let diff = (nums[curr_idx].abs() as usize) % len;
                    let next_idx = (if nums[curr_idx] < 0 { curr_idx + len - diff } else { curr_idx + diff }) % len;

                    nums[curr_idx] = seen;
                    (prev_idx, curr_idx) = (curr_idx, next_idx);
                }

                if prev_idx != curr_idx && nums[prev_idx] == nums[curr_idx] {
                    return true;
                }
            }
        }

        false
    }
}
