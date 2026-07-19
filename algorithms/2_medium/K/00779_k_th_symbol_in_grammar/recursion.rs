impl Solution {
    fn helper(n: i32, k: i32) -> i32 {
        if n == 1 {
            if k != 1 {
                unreachable!("invalid k");
            }
            return 0;
        }
        let parent_pos = (k + 1) / 2;
        let parent_val = Self::helper(n - 1, parent_pos);

        if (k & 1) == 0 { 1 - parent_val } else { parent_val }
    }

    pub fn kth_grammar(n: i32, k: i32) -> i32 {
        assert!(n > 0 && n <= 30 && k > 0);
        return Self::helper(n, k);
    }
}
