impl Solution {
    const MOD_TO: i32 = 1_000_000_007;
    pub fn paths_with_max_score(board: Vec<String>) -> Vec<i32> {
        let n = board.len();
        assert!(n >= 2 && board[0].len() == n);
        let mut buff = vec![0_i32; 2 * ((n + 1) * (n + 1))];
        let (mut sum, mut freq) = buff.split_at_mut((n + 1) * (n + 1));
        freq[n * (n + 1) + n] = 1;

        for i in (0..n).rev() {
            for j in (0..n).rev() {
                let curr_byte = board[i].as_bytes()[j];
                if curr_byte != b'X' {
                    let rd_idx = (i + 1) * (n + 1) + (j + 1);
                    let d_idx = (i + 1) * (n + 1) + j;
                    let r_idx = i * (n + 1) + j + 1;
                    let curr_idx = i * (n + 1) + j;

                    (sum[curr_idx], freq[curr_idx]) = (sum[rd_idx], freq[rd_idx]);

                    if sum[curr_idx] == sum[d_idx] {
                        freq[curr_idx] = (freq[curr_idx] + freq[d_idx]) % Self::MOD_TO;
                    } else if sum[curr_idx] < sum[d_idx] {
                        (sum[curr_idx], freq[curr_idx]) = (sum[d_idx], freq[d_idx])
                    }

                    if sum[curr_idx] == sum[r_idx] {
                        freq[curr_idx] = (freq[curr_idx] + freq[r_idx]) % Self::MOD_TO;
                    } else if sum[curr_idx] < sum[r_idx] {
                        (sum[curr_idx], freq[curr_idx]) = (sum[r_idx], freq[r_idx])
                    }

                    if curr_byte >= b'0' && curr_byte <= b'9' {
                        sum[curr_idx] += (curr_byte - b'0') as i32;
                    }
                }
            }
        }

        if freq[0] == 0 {
            return vec![0, 0];
        }

        vec![sum[0], freq[0]]
    }
}
