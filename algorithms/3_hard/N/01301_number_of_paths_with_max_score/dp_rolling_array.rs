impl Solution {
    const MOD_TO: i32 = 1_000_000_007;
    pub fn paths_with_max_score(board: Vec<String>) -> Vec<i32> {
        let n = board.len();
        assert!(n >= 2 && board[0].len() == n);
        let mut buff = vec![0_i32; 4 * (n + 1)];
        let (mut sum, mut freq) = buff.split_at_mut(2 * (n + 1));
        let (mut curr_sum, mut next_sum) = sum.split_at_mut(n + 1);
        let (mut curr_freq, mut next_freq) = freq.split_at_mut(n + 1);

        for i in (0..n).rev() {
            for j in (0..n).rev() {
                if i == n - 1 && j == n - 1 {
                    curr_freq[j] = 1;
                } else {
                    let curr_byte = board[i].as_bytes()[j];
                    if curr_byte != b'X' {
                        (curr_sum[j], curr_freq[j]) = (next_sum[j + 1], next_freq[j + 1]);

                        if curr_sum[j] == curr_sum[j + 1] {
                            curr_freq[j] = (curr_freq[j] + curr_freq[j + 1]) % Self::MOD_TO;
                        } else if curr_sum[j] < curr_sum[j + 1] {
                            (curr_sum[j], curr_freq[j]) = (curr_sum[j + 1], curr_freq[j + 1]);
                        }

                        if curr_sum[j] == next_sum[j] {
                            curr_freq[j] = (curr_freq[j] + next_freq[j]) % Self::MOD_TO;
                        } else if curr_sum[j] < next_sum[j] {
                            (curr_sum[j], curr_freq[j]) = (next_sum[j], next_freq[j]);
                        }

                        if curr_byte >= b'0' && curr_byte <= b'9' {
                            curr_sum[j] += (curr_byte - b'0') as i32;
                        }
                    }
                }
            }

            (curr_sum, next_sum) = (next_sum, curr_sum);
            (curr_freq, next_freq) = (next_freq, curr_freq);
        }

        if next_freq[0] == 0 {
            return vec![0, 0];
        }

        vec![next_sum[0], next_freq[0]]
    }
}
