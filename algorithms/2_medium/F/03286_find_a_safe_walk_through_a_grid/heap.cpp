typedef ptrdiff_t isize;

constexpr isize directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

class Solution {
public:
    static bool findSafeWalk(vector<vector<int>>& grid, int health) {
        const isize rows = std::ssize(grid);
        assert(rows > 0);
        const isize cols = std::ssize(grid[0]);
        assert(cols > 0 && rows <= 50 && cols <= 50 && health <= rows + cols);

        if (health - grid[0][0] <= 0) {
            return false;
        }

        auto heap = priority_queue<tuple<int8_t, int8_t, int8_t>>();
        auto visited = vector<int8_t>(rows * cols, 0);
        visited[0] = true;
        heap.push({ static_cast<int8_t>(health - grid[0][0]), 0, 0 });

        while (!heap.empty()) {
            const auto [prev_health, i, j] = heap.top();
            heap.pop();

            for (const auto [dx, dy] : directions) {
                const isize ni = i + dx;
                const isize nj = j + dy;

                if (ni < 0 || nj < 0 || ni >= rows || nj >= cols || visited[ni * cols + nj]) {
                    continue;
                }

                const int new_health = prev_health - grid[ni][nj];

                if (ni == rows - 1 && nj == cols - 1) {
                    return new_health > 0;
                }

                if (new_health <= 0) {
                    continue;
                }

                visited[ni * cols + nj] = true;
                heap.push({ static_cast<int8_t>(new_health), static_cast<int8_t>(ni), static_cast<int8_t>(nj) });
            }
        }

        return false;
    }
};
