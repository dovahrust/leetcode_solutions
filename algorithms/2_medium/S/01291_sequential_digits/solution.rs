impl Solution {
    const MAX_HI: i32 = 1_000_000_000;

    pub fn sequential_digits(lo: i32, hi: i32) -> Vec<i32> {
        assert!(lo >= 10 && lo <= hi && hi <= Self::MAX_HI);
        let mut res: Vec<i32> = Vec::new();

        for start_dig in 1..=9_i32 {
            let mut num = 0_i32;

            for dig in start_dig..=9_i32 {
                num = num * 10 + dig;

                if num > hi {
                    break;
                }

                if num >= lo {
                    res.push(num);
                }
            } 
        }

        res.sort_unstable();
        res
    }
}
