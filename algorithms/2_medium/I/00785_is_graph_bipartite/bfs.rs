use std::collections::VecDeque;

impl Solution {
    pub fn is_bipartite(graph: Vec<Vec<i32>>) -> bool {
        let n = graph.len();
        assert!(n >= 1 && n <= 100 && graph.iter().all(|g| g.iter().all(|&node| node >=0 && (node as usize) < n)));
        let mut colors = vec![0_u8; n];
        let mut q: VecDeque<u8> = VecDeque::with_capacity(n);

        for node in 0..n {
            if colors[node] != 0 {
                continue;
            }
            q.push_back(node as u8);
            colors[node] = 1;
            while let Some(parent_u8) = q.pop_front() {
                let parent = parent_u8 as usize;
                let color_parent = colors[parent];
                for &child_i32 in graph[parent].iter() {
                    let child = child_i32 as usize;
                    if colors[child] == color_parent {
                        return false;
                    }
                    if colors[child] != 0 {
                        continue;
                    }
                    if color_parent == 1 {
                        colors[child] = 2;
                    } else {
                        colors[child] = 1;
                    }
                    q.push_back(child as u8);
                }
            }
        }

        true
    }
}
