impl Solution {
    pub fn number_of_substrings(s: String) -> i32 {
        assert!(s.len() < i32::MAX as usize);
        let mut last_seen = [-1_i32; 3];
        let mut cnt = 0_i32;

        for (i, &byte) in s.as_bytes().into_iter().enumerate() {
            assert!(byte >= b'a' && byte <= b'c');
            last_seen[(byte - b'a') as usize] = i as i32;
            cnt += 1 + *last_seen.iter().min().unwrap();
        }

        cnt
    }
}
