impl Solution {
    const VALID_BYTES: [u8; 3] = [b'a', b'b', b'c'];

    fn dfs(temp: &mut [u8], i: usize, cnt: &mut i32, target: i32) {
        if *cnt == target {
            return;
        }

        if i == temp.len() {
            *cnt += 1;
            return;
        }

        for byte in Self::VALID_BYTES {
            if i == 0 || temp[i - 1] != byte {
                temp[i] = byte;
                Self::dfs(temp, i + 1, cnt, target);
            }

            if *cnt == target {
                return;
            }
        }

    }

    pub fn get_happy_string(n: i32, k: i32) -> String {
        let mut cnt = 0_i32;
        let mut temp = vec![b' '; n as usize];
        Self::dfs(&mut temp, 0, &mut cnt, k);
        if cnt == k {
            return String::from_utf8(temp).unwrap();
        }
        String::default()
    }
}
