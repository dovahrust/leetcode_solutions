impl Solution {
    pub fn corp_flight_bookings(bookings: Vec<Vec<i32>>, n: i32) -> Vec<i32> {
        assert!(n >= 0);
        let mut prefix = vec![0_i32; (n + 1) as usize];
        for b in bookings {
            debug_assert!(b.len() == 3);
            let (lo, hi, seats) = (b[0], b[1], b[2]);
            debug_assert!(lo >= 1 && lo <= hi && hi <= n && seats >= 1);
            prefix[(lo - 1) as usize] += seats;
            prefix[hi as usize] -= seats;
        }
        prefix.pop();
        for i in 1..(n as usize) {
            prefix[i] += prefix[i - 1];
        }

        prefix
    }
}
