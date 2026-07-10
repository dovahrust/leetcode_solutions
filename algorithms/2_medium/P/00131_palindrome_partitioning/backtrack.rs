impl Solution {
    #[inline(always)]
    fn is_palindrome(bytes: &[u8]) -> bool {
        assert!(!bytes.is_empty());
        let mut hi = bytes.len() - 1;
        let mut lo = 0_usize;

        while lo < hi {
            if bytes[lo] != bytes[hi] {
                return false;
            }

            lo += 1;
            hi -= 1;
        }

        true
    }

    fn backtrack(bytes: &[u8], lo: usize, res: &mut Vec<Vec<String>>, temp: &mut Vec<String>) {
        let len = bytes.len();

        if lo >= len {
            res.push(temp.clone());
            return;
        }

        for hi in lo..len {
            if Self::is_palindrome(&bytes[lo..=hi]) {
                temp.push(String::from_utf8(bytes[lo..=hi].to_vec()).unwrap());
                Self::backtrack(bytes, hi + 1, res, temp);
                temp.pop();
            }
        }
    }

    pub fn partition(s: String) -> Vec<Vec<String>> {
        let mut res: Vec<Vec<String>> = Vec::default();
        let mut temp: Vec<String> = Vec::default();

        Self::backtrack(s.as_bytes(), 0, &mut res, &mut temp);

        res
    }
}
