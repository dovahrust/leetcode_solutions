use std::collections::BinaryHeap;
use std::cmp::Reverse;

impl Solution {
    #[inline(always)]
    fn init_adj(n: i32, edges: Vec<Vec<i32>>) -> Vec<Vec<(i32, i32)>> {
        let mut adj: Vec<Vec<(i32, i32)>> = vec![Vec::default(); n as usize];
        for e in edges {
            let (u, v, w) = (e[0], e[1], e[2]);
            assert!(u >= 0 && v >= 0 && u < n && v < n && w >= 1 && w <= 1_000_000_000);
            adj[u as usize].push((v, w));
        }
        adj
    }

    pub fn min_time_max_power(n: i32, edges: Vec<Vec<i32>>, power: i32, cost: Vec<i32>, source: i32, target: i32) -> Vec<i64> {
        assert!(
            n >= 1 && n <= 1000 &&
            source >= 0 && source < n &&
            target >= 0 && target < n &&
            power <= 1000 && power >= 0
        );

        let adj = Self::init_adj(n, edges);
        let mut heap: BinaryHeap<(Reverse<i64>, i32, i32)> = BinaryHeap::new();
        let dp_cols = power + 1;
        let mut dp = vec![i64::MAX; (n * dp_cols) as usize];
        let time = 0;
        heap.push((Reverse(time), power, source));
        dp[(source * dp_cols + power) as usize] = time;

        while let Some((Reverse(u_time), u_power, u)) = heap.pop() {
            if u == target {
                return vec![u_time, u_power as i64];
            } else {
                let remain_power = u_power - cost[u as usize];
                if remain_power < 0 {
                    continue;
                }

                for &(v, t) in adj[u as usize].iter() {
                    let new_time = u_time + t as i64;
                    if new_time < dp[(v * dp_cols + remain_power) as usize] {
                        dp[(v * dp_cols + remain_power) as usize] = new_time;
                        heap.push((Reverse(new_time), remain_power, v));
                    }
                }
            }
        }

        vec![-1, -1]
    }
}
