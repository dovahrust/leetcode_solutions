#define MOD 1000000007

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathsWithMaxScore(char ** board, int n, int* res_len)
{
    assert(board != NULL && n >= 2 && res_len != NULL);
    int* res = malloc(2 * sizeof(*res));
    assert(res != NULL);
    *res_len = 2;

    int* buff = calloc(4 * ((size_t)n + 1), sizeof(*buff));
    assert(buff != NULL);
    int* curr_sum = &buff[0];
    int* next_sum = &buff[n + 1];
    int* curr_freq = &buff[2 * (n + 1)];
    int* next_freq = &buff[3 * (n + 1)];

    for (int i = n - 1; i >= 0; i -= 1) {
        for (int j = n - 1; j >= 0; j -= 1) {
            if (i == n - 1 && j == n - 1) {
                curr_freq[j] = 1;
            } else {
                const char curr_char = board[i][j];
                if (curr_char != 'X') {
                    curr_sum[j] = next_sum[j + 1];
                    curr_freq[j] = next_freq[j + 1];

                    if (curr_sum[j] == curr_sum[j + 1]) {
                        curr_freq[j] = (curr_freq[j] + curr_freq[j + 1]) % MOD;
                    } else if (curr_sum[j] < curr_sum[j + 1]) {
                        curr_sum[j] = curr_sum[j + 1];
                        curr_freq[j] = curr_freq[j + 1];
                    }

                    if (curr_sum[j] == next_sum[j]) {
                        curr_freq[j] = (curr_freq[j] + next_freq[j]) % MOD;
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

        int* temp = curr_sum;
        curr_sum = next_sum;
        next_sum = temp;

        temp = curr_freq;
        curr_freq = next_freq;
        next_freq = temp;
    }

    if (next_freq[0] == 0) {
        res[0] = 0;
        res[1] = 0;
    } else {
        res[0] = next_sum[0];
        res[1] = next_freq[0];
    }

/* cleanup: */
    free(buff);
    return res;
}
