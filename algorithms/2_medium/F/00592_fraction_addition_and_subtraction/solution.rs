impl Solution {
    #[inline(always)]
    fn gcd(mut a: i32, mut b: i32) -> i32 {
        while b != 0 {
            let t = b;
            b = a % b;
            a = t;
        }
        a
    }

    #[inline(always)]
    fn extract_nums(bytes: &[u8], start_idx: usize) -> Option<(i32, i32, usize)> {
        if start_idx == bytes.len() {
            return None;
        }

        let mut idx = start_idx;
        let is_pos = match bytes[idx] {
            b'+' => {
                idx += 1;
                true
            },
            b'-' => {
                idx += 1; 
                false
            },
            b'0'..=b'9' => true,
            _ => unreachable!(),
        };

        let (mut num1, mut num2) = (0, 0);
        while let Some(&byte) = bytes.get(idx) && byte != b'/' {
            num1 = num1 * 10 + (byte - b'0') as i32;
            idx += 1;
        }

        idx += 1;
        while let Some(&byte) = bytes.get(idx) && (byte != b'+' && byte != b'-') {
            num2 = num2 * 10 + (byte - b'0') as i32;
            idx += 1;
        }

        Some((if is_pos { num1 } else { -num1 }, num2, idx))
    }

    pub fn fraction_addition(expression: String) -> String {
        let bytes = expression.as_bytes();
        let mut start_idx = 0_usize;
        let (mut n, mut d) = (0, 1);
        while let Some((mut res_n, res_d, new_start_idx)) = Self::extract_nums(bytes, start_idx) {
            let gcd = Self::gcd(res_d, d);
            let lcm = (res_d / gcd) * d;
            res_n = (lcm / res_d) * res_n;
            n = (lcm / d) * n;
            d = lcm;
            n += res_n;
            start_idx = new_start_idx;
        }

        let gcd = Self::gcd(n.abs(), d);
        n /= gcd;
        d /= gcd;

        format!("{}/{}", n, d)
    }
}
