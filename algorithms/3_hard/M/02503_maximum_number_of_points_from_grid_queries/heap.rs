use std::collections::BinaryHeap;
use std::cmp::Reverse;

impl Solution {
    pub fn max_points(grid: Vec<Vec<i32>>, mut queries: Vec<i32>) -> Vec<i32> {
        assert!(grid.len() > 0 && grid[0].len() > 0);
        let (rows, cols) = (grid.len(), grid[0].len());
        assert!(rows <= 1_000 && cols <= 1_000 && queries.len() <= 10_000);

        let mut res = vec![0; queries.len()];
        let mut combos: Vec<(_, _)> = queries.into_iter().enumerate().map(|(i, q)| (q, i as u32)).collect();
        combos.sort_unstable();
        let mut heap: BinaryHeap<(Reverse<i32>, u16, u16)> = BinaryHeap::with_capacity(rows + cols);
        let mut visited = vec![false; rows * cols];
        heap.push((Reverse(grid[0][0]), 0, 0));
        visited[0] = true;
        let mut combos_idx = 0_usize;
        let combos_len = combos.len();
        let mut cnt = 0_i32;

        while let Some((Reverse(val), i_u16, j_u16)) = heap.pop() {
            while combos_idx < combos_len && combos[combos_idx].0 <= val {
                res[combos[combos_idx].1 as usize] = cnt;
                combos_idx += 1;
            }

            if combos_idx == combos_len {
                break;
            }

            let (i_isize, j_isize) = (i_u16 as isize, j_u16 as isize);
            cnt += 1;

            for (dx, dy) in [(-1, 0), (1, 0), (0, -1), (0, 1)] {
                let (ni_isize, nj_isize) = (i_isize + dx, j_isize + dy);
                if ni_isize < 0 || nj_isize < 0 {
                    continue;
                }
                let (ni, nj) = (ni_isize as usize, nj_isize as usize);
                if ni >= rows || nj >= cols || visited[ni * cols + nj] {
                    continue;
                }
                visited[ni * cols + nj] = true;
                let new_val = val.max(grid[ni][nj]);
                heap.push((Reverse(new_val), ni as u16, nj as u16));
            }
        }

        for i in combos_idx..combos_len {
            res[combos[i].1 as usize] = cnt;
        }

        res
    }
}
