impl Solution {
    pub fn shift_grid(grid: Vec<Vec<i32>>, k: i32) -> Vec<Vec<i32>> {
        let rows = grid.len();
        let cols = grid[0].len();
        let shift_counts = (k as usize) % (rows * cols);

        if shift_counts == 0 {
            return grid;
        }

        let mut res = vec![vec![0_i32; cols]; rows];
        let mut res_i = shift_counts / cols;
        let mut res_j = shift_counts % cols;

        for i in 0..rows {
            for j in 0..cols {
                res[res_i][res_j] = grid[i][j];
                res_j += 1;

                if res_j == cols {
                    res_j = 0;
                    res_i += 1;

                    if res_i == rows {
                        res_i = 0;
                    }
                }
            }
        }

        res
    }
}
