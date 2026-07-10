typedef ptrdiff_t isize;

constexpr isize directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Solution {
public:
    static vector<int> maxPoints(const vector<vector<int>>& grid, const vector<int>& queries) {
        assert(std::ssize(grid) > 0 && std::ssize(grid[0]) > 0);
        const isize rows = std::ssize(grid);
        const isize cols = std::ssize(grid[0]);
        assert(rows <= 1'000 && cols <= 1'000 && std::ssize(queries) <= 10'000);

        auto res = vector<int>(std::ssize(queries));
        const isize combos_len = std::ssize(queries);
        auto combos = vector<pair<int, int32_t>>(combos_len);
        for (isize i = 0; i < combos_len; i += 1) {
            combos[i].first = queries[i];
            combos[i].second = static_cast<int32_t>(i);
        }
        ranges::sort(combos, [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
        auto heap = priority_queue<tuple<int, int16_t, int16_t>, vector<tuple<int, int16_t, int16_t>>, greater<>>();
        auto visited = vector<int8_t>(rows * cols, 0);
        heap.push({grid[0][0], 0, 0});
        visited[0] = true;
        isize combos_idx = 0;
        int cnt = 0;

        while (!heap.empty()) {
            const auto [val, i_i16, j_i16] = heap.top();
            heap.pop();
            while (combos_idx < combos_len && combos[combos_idx].first <= val) {
                res[combos[combos_idx].second] = cnt;
                combos_idx += 1;
            }

            if (combos_idx == combos_len) {
                break;
            }

            cnt += 1;

            for (const auto [dx, dy] : directions) {
                const isize ni = dx + i_i16;
                const isize nj = dy + j_i16;
                if (ni < 0 || nj < 0 || ni >= rows || nj >= cols || visited[ni * cols + nj]) {
                    continue;
                }
                visited[ni * cols + nj] = true;
                const int new_val = std::max(val, grid[ni][nj]);
                heap.push({new_val, static_cast<int16_t>(ni), static_cast<int16_t>(nj)});
            }
        }

        for (isize i = combos_idx; i < combos_len; i += 1) {
            res[combos[i].second] = cnt;
        }

        return res;
    }
};
