enum ExtractResult {
    Num(i32, usize),
    X(i32, usize),
    EqualSign(usize),
    None,
}

impl Solution {
    #[inline(always)]
    fn extract_nums(bytes: &[u8], mut idx: usize) -> ExtractResult {
        if idx >= bytes.len() {
            return ExtractResult::None;
        }

        if bytes[idx] == b'=' {
            return ExtractResult::EqualSign(idx + 1);
        }

        let is_pos = match bytes[idx] {
            b'+' => {
                idx += 1;
                true
            },
            b'-' => {
                idx += 1; 
                false
            },
            b'0'..=b'9' | b'x' => true,
            _ => unreachable!(),
        };

        if bytes[idx] == b'x' {
            return ExtractResult::X(if is_pos { 1 } else { -1 }, idx + 1);
        }

        let mut num = 0;
        while let Some(&byte) = bytes.get(idx) && byte >= b'0' && byte <= b'9' {
            num = num * 10 + (byte - b'0') as i32;
            idx += 1;
        }

        match bytes.get(idx) {
            Some(b'x') => ExtractResult::X(if is_pos { num } else { -num }, idx + 1),
            _ => ExtractResult::Num(if is_pos { num } else { -num }, idx)
        }
    }

    pub fn solve_equation(equation: String) -> String {
        let bytes = equation.as_bytes();
        let mut start_idx = 0_usize;
        let (mut num, mut x, mut is_left_op) = (0, 0, true);
        while let state = Self::extract_nums(bytes, start_idx) {
            match state {
                ExtractResult::Num(val, new_start_idx) => {
                    num += if is_left_op { val } else { -val };
                    start_idx = new_start_idx;
                },
                ExtractResult::X(val, new_start_idx) => {
                    x += if is_left_op { val } else { -val };
                    start_idx = new_start_idx;
                },
                ExtractResult::EqualSign(new_start_idx) => {
                    is_left_op = false;
                    start_idx = new_start_idx;
                },
                ExtractResult::None => {
                    break;
                }
            }
        }

        if x == 0 {
            return String::from(if num == 0 { "Infinite solutions" } else { "No solution" });
        }

        num /= x;
        format!("x={}", -num)
    }
}
