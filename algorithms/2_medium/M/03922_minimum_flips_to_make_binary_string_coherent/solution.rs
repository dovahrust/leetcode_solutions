impl Solution {
    pub fn min_flips(s: String) -> i32 {
        let bytes = s.as_bytes();
        assert!(bytes.len() > 0);
        let (mut ones, mut zeros) = (0_usize, 0_usize);

        for &b in bytes {
            match b {
                b'0' => zeros += 1,
                b'1' => ones += 1,
                _ => unreachable!(),
            }
        }

        if zeros == 0 || ones <= 1 {
            return 0;
        }

        let extra_keep_one = if bytes[0] == b'1' && *bytes.last().unwrap() == b'1' { 2 } else { 1 };

        zeros.min(ones - extra_keep_one).try_into().unwrap()
    }
}
