impl Solution {
    pub fn max_satisfaction(mut satisfaction: Vec<i32>) -> i32 {
        debug_assert!(satisfaction.len() >= 1 && satisfaction.len() <= 500 &&
                      satisfaction.iter().all(|x| -1000 <= *x && *x <= 1000));

        satisfaction.sort_unstable();

        let mut res = 0_i32;
        let mut curr_sum = 0_i32;

        for s in satisfaction.into_iter().rev() {
            curr_sum += s;
            let new_res = res + curr_sum;

            if new_res < res {
                break;
            }

            res = new_res;
        }

        res
    }
}
