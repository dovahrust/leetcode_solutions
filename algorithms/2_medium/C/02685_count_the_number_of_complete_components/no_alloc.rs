#[derive(Clone, Copy)]
struct Data {
    edges: i16,
    nodes: i16,
}

impl Solution {
    const MAX_ALLOWED_N: usize = 50;

    pub fn count_complete_components(n: i32, edges: Vec<Vec<i32>>) -> i32 {
        assert!(n >= 1 && (n as usize) <= Self::MAX_ALLOWED_N);
        let mut data = [Data { edges: 0, nodes: 0 }; Self::MAX_ALLOWED_N + 1];
        let mut data_len = 0_usize;
        let mut roots = [0_i8; Self::MAX_ALLOWED_N + 1];
        let mut roots_len = 0_usize;
        let mut to_roots = [-1_i8; Self::MAX_ALLOWED_N + 1];

        for e in edges {
            let (u, v) = (e[0], e[1]);
            assert!(u >= 0 && v >=0 && u < n && v < n);
            let max_root = to_roots[u as usize].max(to_roots[v as usize]);
            let min_root = to_roots[u as usize].min(to_roots[v as usize]);
            if max_root == -1 {
                to_roots[u as usize] = roots_len as i8;
                to_roots[v as usize] = roots_len as i8;
                roots[roots_len] = data_len as i8;
                roots_len += 1;
                data[data_len] = Data { edges: 1, nodes: 2 };
                data_len += 1;
            } else if min_root == -1 {
                to_roots[u as usize] = max_root;
                to_roots[v as usize] = max_root;
                data[roots[max_root as usize] as usize].edges += 1;
                data[roots[max_root as usize] as usize].nodes += 1;
            } else if roots[max_root as usize] == roots[min_root as usize] {
                data[roots[min_root as usize] as usize].edges += 1;
            } else {
                data[roots[min_root as usize] as usize].edges += data[roots[max_root as usize] as usize].edges + 1;
                data[roots[min_root as usize] as usize].nodes += data[roots[max_root as usize] as usize].nodes;
                data[roots[max_root as usize] as usize] = Data { edges: -1, nodes: 0 };
                roots[max_root as usize] = roots[min_root as usize];
            }
        }

        for i in 0..(n as usize) {
            if to_roots[i] == -1 {
                data[data_len] = Data { edges: 0, nodes: 1};
                data_len += 1;
            }
        }

        let mut cnt = 0;
        for d in &data[0..data_len] {
            let expected = (d.nodes * (d.nodes - 1)) / 2;
            if d.edges == expected {
                cnt += 1;
            }
        }
        cnt
    }
}
