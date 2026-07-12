#define DIR_LEN 8

enum state {
    UNSEEN = 'E',
    IN_PROCESS = '#',
    MINE = 'M',
    BLANK = 'B',
    REVEALED_MINE = 'X'
};

struct entity {
    int8_t i;
    int8_t j;
};

const int DIRECTIONS[DIR_LEN][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

static inline int calc_cnt_mines_arround(char** board, const int rows, const int cols, const int i, const int j);
static inline void bfs(char** board, const int rows, const int cols, const int i, const int j);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int rows, int* board_cols, int* click, int click_len, int* return_len, int** return_col_len)
{
    assert(rows > 0 && board_cols[0] > 0 && rows <= 50 && board_cols[0] <= 50);
    const int cols = board_cols[0];
    const int start_i = click[0];
    const int start_j = click[1];
    assert(start_i >= 0 && start_i < rows && start_j >= 0 && start_j < cols);

    *return_len = rows;
    char** res = malloc((size_t)rows * sizeof(*res));
    int* res_cols_len = malloc((size_t)rows * sizeof(*res_cols_len));
    assert(res != NULL && res_cols_len != NULL);
    for (int i = 0; i < rows; i += 1) {
        res_cols_len[i] = cols;
        res[i] = malloc((size_t)cols * sizeof(**res));
        assert(res[i] != NULL);
        for (int j = 0; j < cols; j += 1) { res[i][j] = board[i][j]; }
    }
    *return_col_len = res_cols_len;

    switch (res[start_i][start_j]) {
        case MINE:
            res[start_i][start_j] = REVEALED_MINE;
            break;
        case UNSEEN:
            bfs(res, rows, cols, start_i, start_j);
            break;
        default:
            break;
    }

    return res;
}

static inline int calc_cnt_mines_arround(char** board, const int rows, const int cols, const int i, const int j)
{
    int cnt = 0;
    for (int idx = 0; idx < DIR_LEN; idx += 1) {
        const int ni = i + DIRECTIONS[idx][0];
        const int nj = j + DIRECTIONS[idx][1];
        if (ni < 0 || nj < 0 || ni >= rows || nj >= cols) {
            continue;
        }
        if (board[ni][nj] == MINE) {
            cnt += 1;
        }
    }
    return cnt;
}

static inline void bfs(char** board, const int rows, const int cols, const int i, const int j)
{
    const int q_cap = 2 * (rows + cols);
    struct entity* q = malloc((size_t)q_cap * sizeof(*q));
    assert(q != NULL);
    int q_head = 0;
    int q_len = 1;
    q[0] = (struct entity){ i: (int8_t)i, j: (int8_t)j};
    board[i][j] = IN_PROCESS;

    while (q_len > 0) {
        const int i = q[q_head].i;
        const int j = q[q_head].j;
        q_head = (q_head + 1) % q_cap;
        q_len -= 1;
        const int cnt_mines_arround = calc_cnt_mines_arround(board, rows, cols, i, j);

        if (cnt_mines_arround > 0) {
            board[i][j] = '0' + cnt_mines_arround;
        } else {
            board[i][j] = BLANK;

            for (int idx = 0; idx < DIR_LEN; idx += 1) {
                const int ni = i + DIRECTIONS[idx][0];
                const int nj = j + DIRECTIONS[idx][1];
                if (ni < 0 || nj < 0 || ni >= rows || nj >= cols) {
                    continue;
                }
                if (board[ni][nj] == UNSEEN) {
                    board[ni][nj] = IN_PROCESS;
                    assert(q_len < q_cap);
                    q[(q_head + q_len) % q_cap] = (struct entity){ i: (int8_t)ni, j: (int8_t)nj};
                    q_len += 1;
                }
            }
        }
    }
/* cleanup: */
    free(q);
}
