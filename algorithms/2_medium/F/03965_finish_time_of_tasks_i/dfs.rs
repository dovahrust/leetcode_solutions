impl Solution {
    #[inline(always)]
    fn init_adj(n: i32, edges: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut adj = vec![Vec::default(); n as usize];
        for e in edges {
            let (u, v) = (e[0], e[1]);
            debug_assert!(u >= 0 && v >= 0 && u < n && v < n);
            adj[u as usize].push(v);
        }
        adj
    }

    fn dfs(node: i32, adj: &[Vec<i32>], base_time: &[i32]) -> i64 {
        if adj[node as usize].is_empty() {
            return base_time[node as usize] as i64;
        }

        let mut max = i64::MIN;
        let mut min = i64::MAX;

        for &v in adj[node as usize].iter() {
            let val = Self::dfs(v, adj, base_time);
            max = max.max(val);
            min = min.min(val);
        }

        let curr_node_time = max - min + (base_time[node as usize] as i64);

        max + curr_node_time
    }

    pub fn finish_time(n: i32, edges: Vec<Vec<i32>>, base_time: Vec<i32>) -> i64 {
        let adj = Self::init_adj(n, edges);
        let root = 0_i32;

        Self::dfs(root, &adj, &base_time)
    }
}
