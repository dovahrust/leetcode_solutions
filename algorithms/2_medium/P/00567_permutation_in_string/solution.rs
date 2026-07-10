enum IncDec {
    Inc,
    Dec,
}

impl Solution {
    #[inline(always)]
    fn update_freqs_and_mask(freqs: &mut[isize], idx: usize, state: IncDec, mask_non_zeros: &mut isize) {
        freqs[idx] += match state {
            IncDec::Inc => 1,
            IncDec::Dec => -1,
        };
        if freqs[idx] == 0 {
            *mask_non_zeros &= !(1 << idx);
        } else {
            *mask_non_zeros |= (1 << idx);
        }
    }
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let (b1, b2) = (s1.as_bytes(), s2.as_bytes());
        let (b1_len, b2_len) = (b1.len(), b2.len());
        assert!(b1_len > 0 && b2_len > 0);
        if b2_len < b1_len { return false; }

        let mut freqs = [0_isize; 26];
        let mut mask_non_zeros = 0_isize;

        for &byte in s1.as_bytes() {
            assert!(byte >= b'a' && byte <= b'z');
            Self::update_freqs_and_mask(&mut freqs, (byte - b'a') as usize, IncDec::Dec, &mut mask_non_zeros);
        }

        for i in 0..b2_len {
            let byte_to_insert = b2[i];
            assert!(byte_to_insert >= b'a' && byte_to_insert <= b'z');
            Self::update_freqs_and_mask(&mut freqs, (byte_to_insert - b'a') as usize, IncDec::Inc, &mut mask_non_zeros);
            if i >= b1_len {
                let byte_to_remove = b2[i - b1_len];
                Self::update_freqs_and_mask(&mut freqs, (byte_to_remove - b'a') as usize, IncDec::Dec, &mut mask_non_zeros);
            }

            if mask_non_zeros == 0 {
                return true;
            }
        }

        false
    }
}
