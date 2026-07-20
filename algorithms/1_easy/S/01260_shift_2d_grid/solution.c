/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** shiftGrid(int** grid, const int rows, const int* cols_data, const int k,
                int* return_rows, int** return_cols)
{
    assert(rows > 0 && grid != NULL && cols_data != NULL && return_rows != NULL && return_cols != NULL);
    *return_rows = rows;
    const int cols = cols_data[0];
    int* temp = malloc((size_t)rows * sizeof(*temp));
    assert(temp != NULL);
    for (int i = 0; i < rows; i += 1) {
        temp[i] = cols;
    }
    *return_cols = temp;

    int** res = malloc((size_t)rows * sizeof(*res));
    assert(res != NULL);
    for (int i = 0; i < rows; i += 1) {
        res[i] = malloc((size_t)cols * sizeof(**res));
        assert(res[i] != NULL);
    }
    assert(rows <= INT_MAX / cols);
    const int shift_counts = k % (rows * cols);
    int res_i = shift_counts / cols;
    int res_j = shift_counts % cols;

    for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
            res[res_i][res_j] = grid[i][j];
            res_j += 1;

            if (res_j == cols) {
                res_j = 0;
                res_i += 1;

                if (res_i == rows) {
                    res_i = 0;
                }
            }
        }
    }

    return res;
}
