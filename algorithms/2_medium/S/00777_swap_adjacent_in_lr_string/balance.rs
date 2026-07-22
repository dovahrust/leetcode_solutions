impl Solution {
    pub fn can_transform(start: String, result: String) -> bool {
        let (b1, b2) = (start.as_bytes(), result.as_bytes());
        assert!(b1.len() == b2.len());
        let len = b1.len();
        let (mut l_balance, mut r_balance) = (0_isize, 0_isize);

        for i in 0..len {
            match b1[i] {
                b'R' => r_balance += 1,
                b'L' => l_balance += 1,
                _ => {},
            }

            if r_balance != 0 && l_balance != 0 {
                return false;
            }

            match b2[i] {
                b'R' => r_balance -= 1,
                b'L' => l_balance -= 1,
                _ => {},
            }

            if r_balance < 0 || l_balance > 0 || (r_balance != 0 && l_balance != 0) {
                return false;
            }
        }

        r_balance == 0 && l_balance == 0
    }
}
