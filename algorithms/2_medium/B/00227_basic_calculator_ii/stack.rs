impl Solution {
    pub fn calculate(s: String) -> i32 {
        let mut stack_nums: Vec<i32> = vec![0_i32];
        let mut stack_op: Vec<u8> = Vec::new();
        for &b in s.as_bytes() {
            match b {
                b'0'..=b'9' => {
                    let top = stack_nums.last_mut().unwrap();
                    *top = *top * 10 + (b - b'0') as i32;
                },
                b'/' | b'*' | b'-' | b'+' => {
                    if let Some(op) = stack_op.last() && (*op == b'*' || *op == b'/') {
                        let n2 = stack_nums.pop().unwrap();
                        let n1 = stack_nums.pop().unwrap();
                        match *op {
                            b'*' => stack_nums.push(n1 * n2),
                            _ => stack_nums.push(n1 / n2)
                        }
                        stack_op.pop();
                    }

                    stack_op.push(b);
                    stack_nums.push(0);
                }
                b' ' => {},
                _ => unreachable!(),
            }
        }

        if let Some(op) = stack_op.last() && (*op == b'*' || *op == b'/') {
            let n2 = stack_nums.pop().unwrap();
            let n1 = stack_nums.pop().unwrap();
            match *op {
                b'*' => stack_nums.push(n1 * n2),
                _ => stack_nums.push(n1 / n2)
            }
            stack_op.pop();
        }

        let mut res = stack_nums[0];
        for (i, op) in stack_op.into_iter().enumerate() {
            let n2 = stack_nums[i + 1];
            match op {
                b'+' => res = res + n2,
                b'-' => res = res - n2,
                _ => unreachable!(),
            }
        }

        res
    }
}
