impl Solution {
    const MAX_DEST: i32 = 1_000;

    pub fn car_pooling(mut trips: Vec<Vec<i32>>, capacity: i32) -> bool {
        if trips.is_empty()  { return true; }

        assert!(trips.len() <= 1000);
        debug_assert!(trips.iter().all(|t| {
            t[0] > 0 && t[0] <= 100 &&
            0 <= t[1] && t[1] < t[2] && t[2] <= Self::MAX_DEST
        }));

        let max: i32 = trips.iter().map(|t| t[2]).max().unwrap();
        let mut prefix = vec![0_i32; (max + 1) as usize];

        for t in trips {
            prefix[t[1] as usize] += t[0];
            prefix[t[2] as usize] -= t[0];
        }

        if prefix[0] > capacity {
            return false;
        }

        for i in 1..=(max as usize) {
            prefix[i] += prefix[i - 1];
            if prefix[i] > capacity {
                return false;
            }
        }

        true
    }
}
