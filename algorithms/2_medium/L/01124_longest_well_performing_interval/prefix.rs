impl Solution {
    pub fn longest_wpi(hours: Vec<i32>) -> i32 {
        let len = hours.len();
        assert!(len <= 10_000);
        let mut prefix = vec![-1_i16; len + 2];
        let mid = len + 1;
        prefix[mid] = 0;
        let mut pos = mid;
        let mut res = 0_i32;

        for (i, h) in hours.into_iter().enumerate() {
            pos = if h > 8 { pos + 1 } else { pos - 1 };

            if pos > mid {
                res = (i as i32) + 1;
            } else {
                 if prefix[pos] == -1 {
                    prefix[pos] = i as i16;
                }

                if prefix[pos - 1] != -1 {
                    let curr_width = (i as i32) - (prefix[pos - 1] as i32);
                    res = res.max(curr_width);
                }                
            }
        }

        res
    }
}
