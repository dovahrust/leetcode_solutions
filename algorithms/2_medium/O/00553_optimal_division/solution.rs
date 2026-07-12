impl Solution {
    fn push_num_into_vec(vec: &mut Vec<u8>, mut num: i32) {
        assert!(num >= 2);
        let start_idx = vec.len();
        while num > 0 {
            vec.push((num % 10) as u8 + b'0');
            num /= 10;
        }
        vec[start_idx..].reverse();
    }

    pub fn optimal_division(nums: Vec<i32>) -> String {
        let mut res = Vec::with_capacity(60);

        match nums.len() {
            0 => unreachable!(),
            1 => {
                Self::push_num_into_vec(&mut res, nums[0]);
            },
            2 => {
                Self::push_num_into_vec(&mut res, nums[0]);
                res.push(b'/');
                Self::push_num_into_vec(&mut res, nums[1]);
            },
            _ => {

                Self::push_num_into_vec(&mut res, nums[0]);
                res.push(b'/');
                res.push(b'(');
                Self::push_num_into_vec(&mut res, nums[1]);
                for num in nums.into_iter().skip(2) {
                    res.push(b'/');
                    Self::push_num_into_vec(&mut res, num);
                }
                res.push(b')');
            }
        }

        String::from_utf8(res).unwrap()
    }
}
