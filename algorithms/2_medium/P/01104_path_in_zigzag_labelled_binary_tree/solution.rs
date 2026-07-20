impl Solution {
    #[inline(always)]
    fn calc_pow_2(mut n: i32) -> i32 {
        let mut res = 0;
        while n > 0 {
            res += 1;
            n /= 2;
        }
        res
    }

    pub fn path_in_zig_zag_tree(label: i32) -> Vec<i32> {
        assert!(label >= 1);
        let pow_2 = Self::calc_pow_2(label);
        let mut res = vec![0_i32; pow_2 as usize];
        let mut curr_val = label;
        let mut hi = 2_i32.pow(pow_2 as u32) - 1;
        let mut lo = 2_i32.pow((pow_2 - 1) as u32);

        for i in (0..pow_2 as usize).rev() {
            res[i] = curr_val;

            curr_val = (hi + lo - curr_val) / 2;
            hi /= 2;
            lo /=2;
        }

        res
    }
}
