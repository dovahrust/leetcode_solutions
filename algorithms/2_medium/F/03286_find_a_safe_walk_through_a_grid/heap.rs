use std::collections::BinaryHeap;

impl Solution {
    const DIRECTIONS: [(isize, isize); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

    pub fn find_safe_walk(grid: Vec<Vec<i32>>, health: i32) -> bool {
        assert!(grid.len() > 0 && grid[0].len() > 0);
        let (rows, cols) = (grid.len(), grid[0].len());
        assert!(rows <= 50 && cols <= 50 && health <= (rows + cols) as i32);

        if health - grid[0][0] <= 0 {
            return false;
        }

        let mut heap: BinaryHeap<(i8, i8, i8)> = BinaryHeap::new();
        let mut visited = vec![false; rows * cols];
        visited[0] = true;
        heap.push(((health - grid[0][0]) as i8, 0, 0));

        while let Some((prev_health_i8, i_i8, j_i8)) = heap.pop() {
            let (prev_health, i, j) = (prev_health_i8 as i32, i_i8 as isize, j_i8 as isize);

            for (dx, dy) in Self::DIRECTIONS {
                let (ni_isize, nj_isize) = (i + dx, j + dy);
                if ni_isize < 0 || nj_isize < 0 {
                    continue;
                }

                let (ni, nj) = (ni_isize as usize, nj_isize as usize);
                if ni >= rows || nj >= cols || visited[ni * cols + nj] {
                    continue;
                }

                let new_health = prev_health - grid[ni][nj];

                if ni == rows - 1 && nj == cols - 1 {
                    return new_health > 0;
                }

                if new_health <= 0 {
                    continue;
                }

                visited[ni * cols + nj] = true;
                heap.push((new_health as i8, ni as i8, nj as i8));
            }
        }

        false
    }
}
