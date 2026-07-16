use std::collections::BinaryHeap;
use std::cmp::Reverse;

struct Graph {
    adj: Vec<Vec<(i32, i32)>>,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Graph {

    fn new(n: i32, edges: Vec<Vec<i32>>) -> Self {
        assert!(n >= 1 && n <= 100);
        let n = n as usize;
        let mut adj: Vec<Vec<(i32, i32)>> = vec![Vec::default(); n];
        for e in edges {
            let (u, v, w) = (e[0], e[1], e[2]);
            assert!(u >= 0 && (u as usize) < n &&
                    v >= 0 && (v as usize) < n && w >= 1);

            adj[u as usize].push((v, w));
        }

        Self {
            adj: adj,
        }
    }

    fn add_edge(&mut self, edge: Vec<i32>) {
        let n = self.adj.len();
        let (u, v, w) = (edge[0], edge[1], edge[2]);
        assert!(u >= 0 && (u as usize) < n &&
                v >= 0 && (v as usize) < n && w >= 1);

        self.adj[u as usize].push((v, w));
    }

    fn shortest_path(&self, node1: i32, node2: i32) -> i32 {
        let n = self.adj.len();
        assert!(node1 >= 0 && (node1 as usize) < n &&
                node2 >= 0 && (node2 as usize) < n);

        let mut heap: BinaryHeap<Reverse<(i32, i32)>> = BinaryHeap::new();
        heap.push(Reverse((0, node1)));
        let mut costs = vec![i32::MAX; n];
        costs[node1 as usize] = 0;

        while let Some(Reverse((cost, u))) = heap.pop() {
            if u == node2 {
                return cost;
            }
            if cost > costs[u as usize] {
                continue;
            }
            for &(v, w) in self.adj[u as usize].iter() {
                let new_cost = cost + w;
                if new_cost < costs[v as usize] {
                    costs[v as usize] = new_cost;
                    heap.push(Reverse((new_cost, v)));
                }
            }
        }

        -1
    }
}

/**
 * Your Graph object will be instantiated and called as such:
 * let obj = Graph::new(n, edges);
 * obj.add_edge(edge);
 * let ret_2: i32 = obj.shortest_path(node1, node2);
 */
