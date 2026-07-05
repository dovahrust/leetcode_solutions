use std::collections::VecDeque;

impl Solution {
    #[inline(always)]
    fn calc_adj(edges: Vec<Vec<i32>>, n: i32) -> Vec<Vec<(i32, i32)>> {
        let mut res: Vec<Vec<(i32, i32)>> = vec![Vec::default(); n as usize + 1];
        for e in edges {
            let (u, v, cost) = (e[0], e[1], e[2]);
            res[u as usize].push((v, cost));
            res[v as usize].push((u, cost));
        }
        res
    }

    pub fn min_score(n: i32, roads: Vec<Vec<i32>>) -> i32 {
        assert!(n >= 2);
        let adj = Self::calc_adj(roads, n);
        let mut seen = vec![false; n as usize + 1];
        let mut q: VecDeque<i32> = VecDeque::new();
        let root = 1_i32;
        seen[root as usize] = true;
        q.push_back(root);
        let mut res = i32::MAX;

        while let Some(node) = q.pop_front() {
            for &(v, w) in &adj[node as usize] {
                res = res.min(w);
                if !seen[v as usize] {
                    seen[v as usize] = true;
                    q.push_back(v);
                }
            }
        }

        if !seen[n as usize] { unreachable!("there is no path between 1 and {n}") } else { res }
    }
}
