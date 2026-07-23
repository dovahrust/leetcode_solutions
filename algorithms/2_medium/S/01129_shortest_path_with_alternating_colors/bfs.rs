use std::collections::VecDeque;

#[derive(Clone, Copy, Eq, Ord, PartialEq, PartialOrd)]
enum Colors {
    Red,
    Blue,
}

impl Solution {
    #[inline(always)]
    fn init_adj(n: i32, red_edges: Vec<Vec<i32>>, blue_edges: Vec<Vec<i32>>) -> Vec<Vec<(u8, Colors)>> {
        assert!(n <= 100 && n >= 1);
        let mut adj: Vec<Vec<(u8, Colors)>> = vec![Vec::default(); n as usize];
        for r in red_edges {
            assert!(r.len() == 2 && r[0] >= 0 && r[1] >= 0 && r[0] < n && r[1] < n);
            let (u, v) = (r[0], r[1]);
            adj[u as usize].push((v as u8, Colors::Red));
        }
        for b in blue_edges {
            assert!(b.len() == 2 && b[0] >= 0 && b[1] >= 0 && b[0] < n && b[1] < n);
            let (u, v) = (b[0], b[1]);
            adj[u as usize].push((v as u8, Colors::Blue));
        }
        adj
    }

    pub fn shortest_alternating_paths(n: i32, red_edges: Vec<Vec<i32>>, blue_edges: Vec<Vec<i32>>) -> Vec<i32> {
        let adj = Self::init_adj(n, red_edges, blue_edges);
        let mut res = vec![0_i32; n as usize];
        const INF: u8 = u8::MAX;
        let mut costs = vec![(INF, INF); n as usize];
        let mut q: VecDeque<(u8, Colors, u8)> = VecDeque::with_capacity(2 * n as usize);
        let (st_cost, st_node) = (0, 0);
        q.push_back((st_cost, Colors::Red, st_node));
        q.push_back((st_cost, Colors::Blue, st_node));
        costs[0] = (0, 0);

        while let Some((cost, u_color, u)) = q.pop_front() {
            match u_color {
                Colors::Red => {
                    for &(v, v_color) in &adj[u as usize] {
                        if v_color != Colors::Red && costs[v as usize].1 > cost + 1 {
                            costs[v as usize].1 = cost + 1;
                            q.push_back((cost + 1, Colors::Blue, v));
                        }
                    }
                },
                Colors::Blue => {
                    for &(v, v_color) in &adj[u as usize] {
                        if v_color != Colors::Blue && costs[v as usize].0 > cost + 1 {
                            costs[v as usize].0 = cost + 1;
                            q.push_back((cost + 1, Colors::Red, v));
                        }
                    }
                }
            }
        }

        for (i, (r, b)) in costs.into_iter().enumerate() {
            let min = r.min(b);
            res[i] = if min == INF { -1 } else { min as i32 };
        }

        res
    }
}
