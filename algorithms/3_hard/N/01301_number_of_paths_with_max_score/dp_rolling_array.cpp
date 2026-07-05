typedef ptrdiff_t isize;

constexpr int mod = 1'000'000'007;

class Solution {
public:
    static vector<int> pathsWithMaxScore(const vector<string>& board) {
        const isize n = std::ssize(board);
        assert(n >= 2 && n == std::ssize(board[0]));

        auto buff = vector<int>(4 * (n + 1), 0);

        auto curr_sum = span<int>(&buff[0], n + 1);
        auto next_sum = span<int>(&buff[n + 1], n + 1);
        auto curr_freq = span<int>(&buff[2 * (n + 1)], n + 1);
        auto next_freq = span<int>(&buff[3 * (n + 1)], n + 1);

        for (isize i = n - 1; i >= 0; i -= 1) {
            for (isize j = n - 1; j >= 0; j -= 1) {
                if (i == n - 1 && j == n - 1) {
                    curr_freq[j] = 1;
                } else {
                    const char curr_char = board[i][j];
                    if (curr_char != 'X') {
                        curr_sum[j] = next_sum[j + 1];
                        curr_freq[j] = next_freq[j + 1];

                        if (curr_sum[j] == curr_sum[j + 1]) {
                            curr_freq[j] = (curr_freq[j] + curr_freq[j + 1]) % mod;
                        } else if (curr_sum[j] < curr_sum[j + 1]) {
                            curr_sum[j] = curr_sum[j + 1];
                            curr_freq[j] = curr_freq[j + 1];
                        }

                        if (curr_sum[j] == next_sum[j]) {
                            curr_freq[j] = (curr_freq[j] + next_freq[j]) % mod;
                        } else if (curr_sum[j] < next_sum[j]) {
                            curr_sum[j] = next_sum[j];
                            curr_freq[j] = next_freq[j];
                        }

                        if (curr_char >= '0' && curr_char <= '9') {
                            curr_sum[j] += curr_char - '0';
                        }
                    }
                }
            }

            std::swap(curr_sum, next_sum);
            std::swap(curr_freq, next_freq);
        }

        if (next_freq[0] == 0) {
            return vector<int>{0, 0};
        }

        return vector<int>{next_sum[0], next_freq[0]};
    }
};
