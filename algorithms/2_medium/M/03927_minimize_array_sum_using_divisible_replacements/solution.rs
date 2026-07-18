impl Solution {
    pub fn min_array_sum(nums: Vec<i32>) -> i64 {
        assert!(nums.len() > 0);
        debug_assert!(nums.iter().all(|x| *x >= 1 && *x <= 100_000));
        if nums.iter().any(|x| *x == 1) {
            return nums.len() as i64;
        }
        let max = *nums.iter().max().unwrap();
        let mut freqs = vec![0_i32; (max + 1) as usize];
        for num in nums {
            freqs[num as usize] += 1;
        }
        for i in 1..=max {
            if freqs[i as usize] != 0 {
                let mut curr = i + i;
                while curr <= max {
                    freqs[i as usize] += freqs[curr as usize];
                    freqs[curr as usize] = 0;
                    curr += i;
                }
            }
        }

        let mut res = 0_i64;
        for (i_usize, freq_i32) in freqs.into_iter().enumerate() {
            let freq = freq_i32 as i64;
            let i = i_usize as i64;
            res += i * freq;
        }

        res
    }
}
