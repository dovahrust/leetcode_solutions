use std::collections::BinaryHeap;
use std::cmp::Reverse;

impl Solution {
    const MOD_TO: i64 = 1_000_000_007;

    pub fn max_performance(n: i32, speed: Vec<i32>, efficiency: Vec<i32>, k: i32) -> i32 {
        assert!(k > 0);
        let k = k as usize;
        let mut combo = efficiency.iter().zip(speed.iter()).map(|(a, b)| (*a, *b)).collect::<Vec<_>>();
        combo.sort_unstable();

        let mut heap: BinaryHeap<Reverse<i32>> = BinaryHeap::with_capacity(k + 1);
        let mut max_res = 0_i64;
        let mut sum_speed = 0_i64;

        for &(e, s) in combo.iter().rev() {
            sum_speed += s as i64;
            heap.push(Reverse(s));
            if heap.len() > k {
                let Reverse(s_to_remove) = heap.pop().unwrap();
                sum_speed -= s_to_remove as i64;
            }

            let curr = sum_speed * (e as i64);
            max_res = max_res.max(curr);
        }

        (max_res % Self::MOD_TO).try_into().unwrap()
    }
}
