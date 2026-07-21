impl Solution {
    pub fn max_active_sections_after_trade(s: String) -> i32 {
        let bytes = s.as_bytes();
        let (mut prev, mut curr, mut ones, mut max) = (0_isize, 0_isize, 0_isize, 0_isize);

        for (i, &b) in bytes.iter().enumerate() {
            match b {
                b'1' => {
                    ones += 1;
                    if i > 0 && bytes[i - 1] == b'0' {
                        (prev, curr) = (curr, 0);
                    }
                },
                b'0' => {
                    curr += 1;
                    if prev > 0 && curr > 0 {
                        max = max.max(curr + prev);
                    }
                },
                _ => unreachable!("invalid input"),
            }
        }

        (max + ones).try_into().unwrap()
    }
}
