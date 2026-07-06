impl Solution {
    #[inline(always)]
    fn is_ok(freqs: &[isize]) -> bool {
        for byte in b'A'..=b'z' {
            if freqs[byte as usize] < 0 {
                return false;
            }
        }
        true
    }

    pub fn min_window(s: String, t: String) -> String {
        let s_bytes = s.as_bytes();
        let s_len = s_bytes.len();
        if s_len < t.len() { return String::default(); }
        let mut freqs: [isize; 256] = [0; 256];

        for &byte in t.as_bytes() {
            freqs[byte as usize] -= 1;
        }

        let mut lo = 0;
        let mut res = &s_bytes[0..0];

        for hi in 0..s_len {
            freqs[s_bytes[hi] as usize] += 1;

            while lo <= hi && freqs[s_bytes[lo] as usize] > 0 {
                freqs[s_bytes[lo] as usize] -= 1;
                lo += 1;
            }

            if (res.is_empty() || res.len() > ((hi + 1) - lo)) && Self::is_ok(&freqs) {
                res = &s_bytes[lo..=hi];
            }
        }

        String::from_utf8(res.to_vec()).unwrap()
    }
}
