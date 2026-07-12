use std::collections::VecDeque;

impl Solution {
    const DIRECTIONS: [(isize, isize); 8] = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)];
    const UNSEEN: char = 'E';
    const IN_PROCESS: char = '#';
    const MINE: char = 'M';
    const BLANK: char = 'B';
    const REVEALED_MINE: char = 'X';

    #[inline(always)]
    fn cnt_mines_arround(board: &[Vec<char>], cols: usize, i: usize, j: usize) -> i32 {
        let rows = board.len();
        let mut cnt = 0;
        for (dx, dy) in Self::DIRECTIONS {
            let (ni, nj) = (i as isize + dx, j as isize + dy);
            if ni < 0 || nj < 0 || (ni as usize) >= rows || (nj as usize) >= cols {
                continue;
            }
            if board[ni as usize][nj as usize] == Self::MINE {
                cnt += 1;
            }
        }
        cnt
    }

    #[inline(always)]
    fn bfs(board: &mut [Vec<char>], cols: usize, start_i: usize, start_j: usize) {
        let rows = board.len();
        let mut q = VecDeque::with_capacity(2 * (rows + cols));
        q.push_back((start_i as u8, start_j as u8));
        board[start_i][start_j] = Self::IN_PROCESS;

        while let Some((i_u8, j_u8)) = q.pop_front() {
            let (i, j) = (i_u8 as usize, j_u8 as usize);
            let cnt_mines_arround = Self::cnt_mines_arround(&board, cols, i, j);

            if cnt_mines_arround > 0 {
                board[i][j] = (b'0' + cnt_mines_arround as u8) as char;
            } else {
                board[i][j] = Self::BLANK;

                for (dx, dy) in Self::DIRECTIONS {
                    let (ni, nj) = (i as isize + dx, j as isize + dy);
                    if ni < 0 || nj < 0 || (ni as usize) >= rows || (nj as usize) >= cols {
                        continue;
                    }
                    let (ni, nj) = (ni as usize, nj as usize);
                    if board[ni][nj] == Self::UNSEEN {
                        board[ni][nj] = Self::IN_PROCESS;
                        q.push_back((ni as u8, nj as u8));
                    }
                }
            }
        }
    }

    pub fn update_board(mut board: Vec<Vec<char>>, click: Vec<i32>) -> Vec<Vec<char>> {
        assert!(board.len() > 0);
        let (rows, cols) = (board.len(), board[0].len());
        assert!(rows <= 50 && cols <= 50);
        let (start_i, start_j) = (click[0], click[1]);
        assert!(start_i >= 0 && (start_i as usize) < rows && start_j >= 0 && (start_j as usize) < cols);
        let (start_i, start_j) = (start_i as usize, start_j as usize);

        match board[start_i][start_j] {
            Self::MINE => board[start_i][start_j] = Self::REVEALED_MINE,
            Self::UNSEEN => Self::bfs(&mut board, cols, start_i, start_j),
            _ => {},
        }

        board
    }
}
