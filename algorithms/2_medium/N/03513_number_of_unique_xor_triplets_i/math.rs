impl Solution {
    pub fn unique_xor_triplets(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n <= 2 {
            return n as i32;
        }

        let mut res = 1_usize;
        while n >= res {
            res = res << 1;
        }

        res.try_into().unwrap()
    }
}
