impl Solution {
    pub fn smallest_subsequence(s: String) -> String {
        let bytes = s.as_bytes();
        let len = bytes.len();
        assert!(len >= 1 && len <= 1000);
        let mut stack: Vec<u8> = Vec::with_capacity(len);
        let mut freqs = [0_u16; 26];
        for &b in bytes {
            assert!(b >= b'a' && b <= b'z');
            freqs[(b - b'a') as usize] += 1;
        }
        let mut seen = [false; 26];
        for &b in bytes {
            if !seen[(b - b'a') as usize] {
                while let Some(top) = stack.last() && *top >= b && freqs[(*top - b'a') as usize] >= 1 {
                    seen[(*top - b'a') as usize] = false;
                    stack.pop();
                }
                seen[(b - b'a') as usize] = true;
                stack.push(b);
            }
            freqs[(b - b'a') as usize] -= 1;
        }
        String::from_utf8(stack).unwrap()
    }
}
