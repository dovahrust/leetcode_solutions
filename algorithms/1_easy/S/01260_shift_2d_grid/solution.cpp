class Solution {
public:
    static vector<vector<int>> shiftGrid(const vector<vector<int>>& grid, const int k) {
        const size_t rows = grid.size();
        const size_t cols = grid[0].size();
        const size_t shift_counts = static_cast<size_t>(k) % (rows * cols);

        auto res = vector<vector<int>>(rows, vector<int>(cols, 0));
        size_t res_i = shift_counts / cols;
        size_t res_j = shift_counts % cols;

        for (size_t i = 0; i < rows; i += 1) {
            for (size_t j = 0; j < cols; j += 1) {
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
};
