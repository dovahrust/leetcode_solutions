impl Solution {
    pub fn break_palindrome(palindrome: String) -> String {
        let mut bytes = palindrome.into_bytes();
        let len = bytes.len();
        assert!(len > 0);
        // If len is 1, there is no way to break the palindrome.
        if len == 1 { return String::default(); }

        // If the length is odd, we must ignore the middle character.
        // Changing the middle character would still result in a palindrome.
        let half = len / 2;

        for i in 0..half {
            if bytes[i] != b'a' {
                bytes[i] = b'a';
                return String::from_utf8(bytes).unwrap();
            }
        }

        // If we reach here, the string consists only of 'a's.
        bytes[len - 1] = b'b';
        String::from_utf8(bytes).unwrap()
    }
}
