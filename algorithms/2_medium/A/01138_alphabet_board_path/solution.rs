impl Solution {
    pub fn alphabet_board_path(target: String) -> String {
        let (mut i, mut j) = (0_usize, 0_usize);
        let mut res: Vec<u8> = Vec::with_capacity(5 * target.len());

        for &b in target.as_bytes() {
            assert!(b >= b'a' && b <= b'z');
            let new_i = ((b - b'a') / 5) as usize;
            let new_j = ((b - b'a') % 5) as usize;

            while j > new_j {
                res.push(b'L');
                j -= 1;
            }

            while i > new_i {
                res.push(b'U');
                i -= 1;
            }

            while i < new_i {
                res.push(b'D');
                i += 1;
            }

            while j < new_j {
                res.push(b'R');
                j += 1;
            }

            res.push(b'!');
        }

        String::from_utf8(res).unwrap()
    }
}
