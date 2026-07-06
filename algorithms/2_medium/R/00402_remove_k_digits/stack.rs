impl Solution {
    pub fn remove_kdigits(num: String, mut k: i32) -> String {
        let mut bytes = num.into_bytes();
        assert!(bytes.len() > 0);
        let mut stack_len = 0_usize;

        for i in 0..bytes.len() {
            while k > 0 && stack_len > 0 && bytes[stack_len - 1] > bytes[i] {
                stack_len -= 1;
                k -= 1;
            }

            if stack_len == 0 && bytes[i] == b'0' {
                continue;
            }

            bytes[stack_len] = bytes[i];
            stack_len += 1;
        }

        stack_len -= std::cmp::min(stack_len, k as usize);

        if stack_len == 0 {
            bytes[stack_len] = b'0';
            stack_len += 1;
        }

        bytes.truncate(stack_len);

        String::from_utf8(bytes).unwrap()
    }
}
