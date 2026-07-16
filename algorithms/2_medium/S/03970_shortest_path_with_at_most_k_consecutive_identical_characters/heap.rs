use std::collections::BinaryHeap;
use std::cmp::Reverse;

impl Solution {
    #[inline(always)]
    fn init_adj(n: i32, edges: Vec<Vec<i32>>) -> Vec<Vec<(i32, i32)>> {
        let mut adj = vec![Vec::default(); n as usize];
        for e in edges {
            let (u, v, w) = (e[0], e[1], e[2]);
            debug_assert!(u >= 0 && v >= 0 && w >= 1 && u < n && v < n);
            adj[u as usize].push((v, w));
        }
        adj
    }

    pub fn shortest_path(n: i32, edges: Vec<Vec<i32>>, labels: String, k: i32) -> i32 {
        let bytes = labels.as_bytes();
        assert!(n >= 1 && k >= 1 && k <= 50 && (n as usize) == bytes.len());
        let (start_node, target_node) = (0_i32, n - 1);
        let adj = Self::init_adj(n, edges);
        let cost_cols = 1 + k as usize;
        let mut costs = vec![i32::MAX; cost_cols * (n as usize)];
        let mut heap = BinaryHeap::new();
        let start_consecutive = 1_i32;
        heap.push(Reverse((0_i32, start_node, start_consecutive)));
        costs[(start_node as usize) * cost_cols + (start_consecutive as usize)] = 0;

        while let Some(Reverse((cost, u, consecutive))) = heap.pop() {
            if u == target_node {
                return cost;
            }
            if cost > costs[(u as usize) * cost_cols + (consecutive as usize)] {
                continue;
            }
            for &(v, w) in adj[u as usize].iter() {
                let new_cost = cost + w;
                let new_consecutive = if bytes[u as usize] == bytes[v as usize] { 
                    consecutive + 1
                } else {
                    1
                };

                if new_consecutive > k || new_cost >= costs[(v as usize) * cost_cols + (new_consecutive as usize)] {
                    continue;
                }
                costs[(v as usize) * cost_cols + (new_consecutive as usize)] = new_cost;
                heap.push(Reverse((new_cost, v, new_consecutive)));
            }
        }

        -1
    }
}
