impl Solution {
    pub fn largest1_bordered_square(grid: Vec<Vec<i32>>) -> i32 {
        assert!(grid.len() > 0 && grid[0].len() > 0);
        let rows = grid.len();
        let cols = grid[0].len();
        assert!(rows <= 100 && cols <= 100);
        let mut prefix = vec![(0_i8, 0_i8); rows * cols];
        for i in 0..rows {
            for j in 0..cols {
                let mut val = 0;
                if grid[i][j] == 1 {
                    prefix[i * cols + j] = (1, 1);
                }
                if i > 0 {
                    prefix[i * cols + j] .0 += prefix[(i - 1) * cols + j].0;
                }
                if j > 0 {
                    prefix[i * cols + j].1 += prefix[i * cols + j - 1].1;
                }
            }
        }

        let mut res = 0_i8;
        for i in 0..rows {
            for j in 0..cols {
                let (mut ni, mut nj) = (i + res as usize, j + res as usize);
                while ni < rows && nj < cols {
                    let expect = (ni - i + 1) as i8;
                    let up = prefix[i * cols  + nj].1 - if j == 0 { 0 } else { prefix[i * cols  + j - 1 ].1 };
                    let le = prefix[ni * cols  + j].0 - if i == 0 { 0 } else { prefix[(i - 1) * cols  + j].0 };
                    if le != expect || up != expect {
                        break;
                    }
                    let dw = prefix[ni * cols  + nj].1 - if j == 0 { 0 } else { prefix[ni * cols  + j - 1 ].1 };
                    let ri = prefix[ni * cols  + nj].0 - if i == 0 { 0 } else { prefix[(i - 1) * cols  + nj].0 };
                    if dw == expect && ri == expect {   
                        res = expect;
                    }
                    ni += 1;
                    nj += 1;
                }
            }
        }

        (res as i32).pow(2)
    }
}
