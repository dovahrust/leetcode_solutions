impl Solution {
    pub fn min_cost_to_move_chips(position: Vec<i32>) -> i32 {
        let mut cnt = [0_isize; 2];

        for p in position {
            cnt[(p & 1) as usize] += 1;
        }

        cnt[0].min(cnt[1]).try_into().unwrap()
    }
}
