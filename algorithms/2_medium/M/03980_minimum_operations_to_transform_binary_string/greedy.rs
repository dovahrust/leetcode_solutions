impl Solution {
    pub fn min_operations(s1: String, s2: String) -> i32 {
        let (b1, b2) = (s1.as_bytes(), s2.as_bytes());
        assert!(b1.len() > 0 && b1.len() == b2.len());
        let len = b1.len();

        if len == 1 && b1[0] == b'1' && b2[0] == b'0' {
            return -1;
        }

        let mut cnt = 0_isize;
        let mut i = 0_usize;

        while i < len {
            if b1[i] != b2[i] {
                match b1[i] {
                    b'1' => {
                        if i + 1 < len && b1[i + 1] == b'1' && b2[i + 1] == b'0' {
                            cnt += 1;
                            i += 2;
                        } else {
                            cnt += 2;
                            i += 1;
                        }
                    },
                    b'0' => {
                        cnt += 1;
                        i += 1;
                    } ,
                    _ => unreachable!()
                }
            } else {
                i += 1;
            }
        }

        cnt.try_into().unwrap()
    }
}
