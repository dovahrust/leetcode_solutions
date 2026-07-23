struct cell {
    int8_t i;
    int8_t j;
};

int largest1BorderedSquare(int** grid, const int rows, const int* cols_data){
    assert(rows > 0 && rows <= 100 && cols_data != NULL &&
           cols_data[0] > 0 && cols_data[0] <= 100 && grid != NULL);

    const int cols = cols_data[0];
    struct cell* prefix = calloc((size_t)(rows * cols), sizeof(*prefix));
    assert(prefix != NULL);
    for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
            if (grid[i][j] == 1) {
                prefix[i * cols + j].i = 1;
                prefix[i * cols + j].j = 1;
            }
            if (i > 0) {
                prefix[i * cols + j].i += prefix[(i - 1) * cols + j].i;
            }
            if (j > 0) {
                prefix[i * cols + j].j += prefix[i * cols + j - 1].j;
            }
        }
    }

    int8_t res = 0;
    for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
            int ni = i + res;
            int nj = j + res;
            while (ni < rows && nj < cols) {
                int8_t expect = (int8_t)(ni - i + 1);
                const int8_t up = prefix[i * cols  + nj].j - (j == 0 ? 0 : prefix[i * cols  + j - 1 ].j);
                const int8_t le = prefix[ni * cols  + j].i - (i == 0 ? 0 : prefix[(i - 1) * cols  + j].i);
                if (le != expect || up != expect) {
                    break;
                }
                const int8_t dw = prefix[ni * cols  + nj].j - (j == 0 ? 0 : prefix[ni * cols  + j - 1 ].j);
                const int8_t ri = prefix[ni * cols  + nj].i - (i == 0 ? 0 : prefix[(i - 1) * cols  + nj].i);
                if (dw == expect && ri == expect) {
                    res = expect;
                }
                ni += 1;
                nj += 1;
            }
        }
    }

/* cleanup: */
    free(prefix);
    return (int)res * res;
}
