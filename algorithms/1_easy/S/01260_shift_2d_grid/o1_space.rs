impl Solution {
    #[inline(always)]
    fn revers_mat(grid: &mut [Vec<i32>], cols: usize, mut lo: (usize, usize), mut hi: (usize, usize)) {
        while hi != lo {
            let temp = grid[hi.0][hi.1];
            grid[hi.0][hi.1] = grid[lo.0][lo.1];
            grid[lo.0][lo.1] = temp;
            
            lo.1 += 1;
            if lo.1 == cols {
                lo.0 += 1;
                lo.1 = 0;
            }
            if lo == hi {
                break;
            }
            if hi.1 == 0 {
                hi.1 = cols - 1;
                hi.0 -= 1;
            } else {
                hi.1 -= 1;
            }
        }
    }

    pub fn shift_grid(mut grid: Vec<Vec<i32>>, k: i32) -> Vec<Vec<i32>> {
        let rows = grid.len();
        let cols = grid[0].len();
        let shift_counts = (k as usize) % (rows * cols);

        if shift_counts == 0 {
            return grid;
        }

        let mut pivot_i = rows - 1 - shift_counts / cols;
        let mut pivot_j = cols - shift_counts % cols;
        if pivot_j == cols {
            pivot_j = 0;
            pivot_i += 1;
        }
        let d1 = (0_usize, 0_usize);
        let u1 = if pivot_j == 0 {
            // "shift_counts == 0" is checked, so pivot_i, pivot_j cant be 0 at same time
            // For that "pivot_i - 1" is safe 
            (pivot_i - 1, cols - 1)
        } else {
            (pivot_i, pivot_j - 1)
        };

        let d2 = (pivot_i, pivot_j);
        let u2 = (rows - 1, cols - 1);

        Self::revers_mat(&mut grid, cols, d1, u1);
        Self::revers_mat(&mut grid, cols, d2, u2);
        Self::revers_mat(&mut grid, cols, d1, u2);

        grid
    }
}
