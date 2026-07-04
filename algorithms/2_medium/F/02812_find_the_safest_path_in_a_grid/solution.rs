use std::collections::{VecDeque, BinaryHeap};

impl Solution {
    const DIRECTIONS: [(isize, isize); 4] = [(1, 0), (-1, 0), (0, 1), (0, -1)];

    #[inline(always)]
    fn calc_scores(grid: Vec<Vec<i32>>) -> Vec<i32> {
        let n = grid.len();
        let mut q: VecDeque<(i16, i16)>  = VecDeque::with_capacity(n * n);
        let mut scores = vec![-1; n * n];

        for i in 0..n {
            for j in 0..n {
                if grid[i][j] == 1 {
                    q.push_back((i as i16, j as i16));
                    scores[i * n + j] = 0;
                }
            }
        }

        let mut curr_score = 1;
        while !q.is_empty() {
            let q_len = q.len();
            for _ in 0..q_len {
                let (i_i16, j_i16) = q.pop_front().unwrap();
                let (i, j) = (i_i16 as isize, j_i16 as isize);
                for (dx, dy) in Self::DIRECTIONS {
                    let (ni_isize, nj_isize) = (i + dx, j + dy);
                    if ni_isize < 0 || nj_isize < 0 {
                        continue;
                    }

                    let (ni, nj) = (ni_isize as usize, nj_isize as usize);
                    if ni >= n || nj >= n || scores[ni * n + nj] != -1 {
                        continue;
                    }
                    scores[ni * n + nj] = curr_score;
                    q.push_back((ni as i16, nj as i16));
                }
            }
            curr_score += 1;
        }
        
        scores
    }
    pub fn maximum_safeness_factor(grid: Vec<Vec<i32>>) -> i32 {
        let n = grid.len();
        assert!(n > 0 && n <= 400 && n == grid[0].len());
        if grid[0][0] == 1 || grid[n - 1][n - 1] == 1 { return 0; }

        let mut scores = Self::calc_scores(grid);
        let mut heap: BinaryHeap<(i32, i16, i16)> = BinaryHeap::new();
        heap.push((scores[0], 0, 0));
        scores[0] = -1;

        while let Some((curr_score, i_i16, j_i16)) = heap.pop() {
            let (i, j) = (i_i16 as isize, j_i16 as isize);
            for (dx, dy) in Self::DIRECTIONS {
                let (ni_isize, nj_isize) = (i + dx, j + dy);
                if ni_isize < 0 || nj_isize < 0 {
                    continue;
                }

                let (ni, nj) = (ni_isize as usize, nj_isize as usize);
                if ni >= n || nj >= n || scores[ni * n + nj] <= 0 {
                    continue;
                }

                let new_score = curr_score.min(scores[ni * n + nj]);
                if ni == n - 1 && nj == n - 1 {
                    return new_score;
                }

                scores[ni * n + nj] = -1;
                heap.push((new_score, ni as i16, nj as i16));
            }
        }

        0
    }
}
