#[derive(Clone, Copy, PartialEq, Eq)]
enum State {
    Seen,
    InProcess,
    None,
}

impl Solution {
    #[inline(always)]
    fn calc_next_idx(curr: usize, len: usize, num: i32) -> usize {
        let (curr, len, num) = (curr as isize, len as isize, num as isize);
        ((((curr + num) % len) + len) % len) as usize
    }

    pub fn circular_array_loop(nums: Vec<i32>) -> bool {
        let len = nums.len();
        let mut states = vec![State::None; len];

        for i in 0..len {
            if states[i] == State::None {
                let mut curr = i;
                while states[curr] == State::None {
                    states[curr] = State::InProcess;
                    curr = Self::calc_next_idx(curr, len, nums[curr]);
                }

                let mut cycle_len = 0_usize;
                let direction = nums[curr] > 0;
                let mut valid = true;
                while states[curr] == State::InProcess {
                    if (nums[curr] > 0) != direction {
                        valid = false;
                    }
                    states[curr] = State::Seen;
                    curr = Self::calc_next_idx(curr, len, nums[curr]);
                    cycle_len += 1;
                }

                if valid && cycle_len > 1 {
                    return true;
                }

                curr = i;
                while states[curr] == State::InProcess {
                    states[curr] = State::Seen;
                    curr = Self::calc_next_idx(curr, len, nums[curr]);
                }
            }
        }

        false
    }
}
