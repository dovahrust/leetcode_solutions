impl Solution {
    pub fn reverse_parentheses(s: String) -> String {
        let bytes = s.as_bytes();
        let len = bytes.len();
        assert!(len > 0 && len <= 2000);
        let mut stack: Vec<u16> = Vec::with_capacity(len);
        let mut res: Vec<u8> = Vec::with_capacity(len);

        for &b in bytes {
            match b {
                b'(' => {
                    stack.push(res.len() as u16);
                },
                b')' => {
                    let lo = stack.pop().expect("invalid input") as usize;
                    res[lo..].reverse();
                },
                _ => {
                    res.push(b);
                }
            }
        }

        String::from_utf8(res).unwrap()
    }
}
