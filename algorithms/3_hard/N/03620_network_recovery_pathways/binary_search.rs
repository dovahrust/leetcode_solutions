use std::collections::VecDeque;
type DegCntUsedCnt = (i32, i32);

impl Solution {
    #[inline(always)]
    fn calc_adj(edges: Vec<Vec<i32>>, online: Vec<bool>) -> Vec<Vec<(i32, i32)>> {
        let mut res: Vec<Vec<(i32, i32)>> = vec![Vec::default(); online.len()];
        for e in edges {
            let (u, v, cost) = (e[0], e[1], e[2]);
            debug_assert!((u as usize) < online.len() && (v as usize) < online.len() && cost >= 0);
            if online[u as usize] && online[v as usize] {
                res[u as usize].push((v, cost));
            }
        }
        res
    }

    #[inline(always)]
    fn calc_deg(adj: &[Vec<(i32, i32)>]) -> Vec<DegCntUsedCnt> {
        let mut res: Vec<DegCntUsedCnt> = vec![(0, 0); adj.len()];
        for a in adj {
            for &(v, _) in a {
                res[v as usize].0 += 1;
            }
        }

        for (u, a) in adj.iter().enumerate().skip(1) {
            if res[u as usize].0 == 0 {
                for &(v, _) in a {
                    res[v as usize].0 -= 1;
                }
            }
        }

        res
    }

    fn check(adj: &[Vec<(i32, i32)>], q: &mut VecDeque<i32>, costs: &mut [i64], deg: &mut [DegCntUsedCnt], mid: i32, target: i32, k: i64) -> bool {
        costs.iter_mut().for_each(|x| *x = i64::MAX / 2);
        deg.iter_mut().for_each(|x| x.1 = 0);
        q.clear();
        q.push_back(0);
        costs[0] = 0;

        while let Some(node) = q.pop_front() {
            let total_cost = costs[node as usize];

            for &(v, cost) in adj[node as usize].iter() {
                deg[v as usize].1 += 1;
                if deg[v as usize].0 == deg[v as usize].1 {
                    q.push_back(v);
                }
                if cost >= mid {
                    costs[v as usize] = costs[v as usize].min(total_cost + cost as i64);
                }
            }
        }

        costs[target as usize] <= k
    }

    pub fn find_max_path_score(edges: Vec<Vec<i32>>, online: Vec<bool>, k: i64) -> i32 {
        if edges.is_empty() { return -1; }

        let mut lo = i32::MAX;
        let mut hi = 0_i32;
        for e in edges.iter() {
            lo = lo.min(e[2]);
            hi = hi.max(e[2]);
        }

        let target = online.len() as i32 - 1;
        let mut q: VecDeque<i32> = VecDeque::new();
        let mut costs = vec![0_i64; online.len()];
        let adj = Self::calc_adj(edges, online);
        let mut deg = Self::calc_deg(&adj);

        if !Self::check(&adj, &mut q, &mut costs, &mut deg, lo, target, k) {
            return -1;
        }

        while lo <= hi {
            let mid = lo + (hi - lo) / 2;
            if Self::check(&adj, &mut q, &mut costs, &mut deg, mid, target, k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        hi
    }
}
