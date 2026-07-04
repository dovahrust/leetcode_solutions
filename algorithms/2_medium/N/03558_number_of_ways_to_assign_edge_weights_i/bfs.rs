use std::collections::VecDeque;

impl Solution {
    const MOD_TO: i32 = 1_000_000_007;

    #[inline(always)]
    fn mod_pow(base: i32, mut exp: i32, mod_to: i32) -> i32 {
        let mut base = base as i64;
        let mod_to = mod_to as i64;
        let mut res = 1_i64;
        while exp > 0 {
            if exp & 1 == 1 {
                res = (res * base) % mod_to;
            }
            base = (base * base) % mod_to;
            exp >>= 1;
        }
        res as i32
    }

    pub fn assign_edge_weights(edges: Vec<Vec<i32>>) -> i32 {
        let n = edges.len() + 1;

        let mut adj: Vec<Vec<i32>> = vec![Vec::default(); n + 1];
        for e in edges {
            adj[e[0] as usize].push(e[1]);
            adj[e[1] as usize].push(e[0]);
        }

        let mut q: VecDeque<i32> = VecDeque::new();
        let mut visited = vec![false; n + 1];
        let root = 1_i32;
        q.push_back(root);
        visited[root as usize] = true;
        let mut level = 0;
        while !q.is_empty() {
            let q_len = q.len();
            for _ in 0..q_len {
                let node = q.pop_front().unwrap();
                for &other_node in &adj[node as usize] {
                    if !visited[other_node as usize] {
                        visited[other_node as usize] = true;
                        q.push_back(other_node);
                    }
                }
            }
            level += 1;
        }
        let edges_max_depth = level - 1;
        if edges_max_depth  == 0 { return 0; }

        Self::mod_pow(2, edges_max_depth - 1, Self::MOD_TO)
    }
}
