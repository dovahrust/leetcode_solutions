impl Solution {
    fn decrease_cnt_from_freqs(freqs: &mut [usize], idxs: &[usize], mut cnt: i32) {
        assert!(cnt > 0);
        for &i in idxs {
            while freqs[i] > 0 && cnt > 0 {
                freqs[i] -= 1;
                cnt -= 1;
            }

            if cnt == 0 {
                return;
            }
        }
        unreachable!("logical error\n")
    }

    pub fn largest_multiple_of_three(digits: Vec<i32>) -> String {
        let mut freqs = [0_usize; 10];
        let mut rems = [0_usize; 3];
        let mut sum = 0;
        for d in digits {
            assert!(d >= 0 && d <= 9);
            sum += d;
            freqs[d as usize] += 1;
            rems[(d % 3) as usize] += 1;
        }

        match sum % 3 {
            1 => {
                if rems[1] > 0 {
                    Self::decrease_cnt_from_freqs(&mut freqs, &[1, 4, 7], 1);
                } else if rems[2] > 1 {
                    Self::decrease_cnt_from_freqs(&mut freqs, &[2, 5, 8], 2);
                } else {
                    unreachable!("logical error\n")
                }
            },
            2 => {
                if rems[2] > 0 {
                    Self::decrease_cnt_from_freqs(&mut freqs, &[2, 5, 8], 1);
                } else if rems[1] > 1 {
                    Self::decrease_cnt_from_freqs(&mut freqs, &[1, 4, 7], 2);
                } else {
                    unreachable!("logical error\n")
                }
            },
            _ => {}
        }

        if freqs.iter().skip(1).all(|x| *x == 0) {
            if freqs[0] > 0 {
                return String::from("0");
            } else {
                return String::default();
            }
        }

        let total_freqs: usize = freqs.iter().map(|x| *x).sum();
        let mut bytes = vec![0_u8; total_freqs];
        let mut idx = 0_usize;
        for i in (0..=9).rev() {
            for _ in 0..freqs[i] {
                bytes[idx] = i as u8 + b'0';
                idx += 1;
            }
        }
        String::from_utf8(bytes).unwrap()
    }
}
