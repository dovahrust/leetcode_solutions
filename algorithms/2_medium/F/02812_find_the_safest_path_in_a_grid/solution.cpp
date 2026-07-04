typedef ptrdiff_t isize;

static constexpr isize direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class Solution {
    static inline vector<int> calc_scores(const vector<vector<int>>& grid) {
        const isize n = std::ssize(grid);
        assert(n <= 400);
        auto q = queue<pair<int16_t, int16_t>>();
        auto scores = vector<int>(n * n, -1);

        for (isize i = 0; i < n; i += 1) {
            for (isize j = 0; j < n; j += 1) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    scores[i * n + j] = 0;
                }
            }
        }

        int curr_score = 1;
        while (!q.empty()) {
            const isize q_len = std::ssize(q);
            for (isize step = 0; step < q_len; step += 1) {
                const auto [i, j] = q.front();
                q.pop();
                for (const auto [dx, dy] : direction) {
                    const isize ni = i + dx;
                    const isize nj = j + dy;

                    if (ni < 0 || nj < 0 || ni >= n || nj >= n || scores[ni * n + nj] != -1) {
                        continue;
                    }

                    scores[ni * n + nj] = curr_score;
                    q.push({static_cast<int16_t>(ni), static_cast<int16_t>(nj)});
                }
            }
            curr_score += 1;
        }
        
        return scores;
    }

public:
    static int maximumSafenessFactor(const vector<vector<int>>& grid) {
        const isize n = std::ssize(grid);
        assert(n > 0 && n <= 400 && n == std::ssize(grid[0]));
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) { return 0; }

        auto scores = calc_scores(grid);
        auto heap = priority_queue<tuple<int, int16_t, int16_t>>();
        heap.push({scores[0], 0, 0});
        scores[0] = -1;

        while (!heap.empty()) {
            const auto [curr_score, i, j] = heap.top();
            heap.pop();
    
            for (const auto [dx, dy] : direction) {
                const isize ni = i + dx;
                const isize nj = j + dy;

                if (ni < 0 || nj < 0 || ni >= n || nj >= n || scores[ni * n + nj] <= 0) {
                    continue;
                }

                const int new_score = std::min(curr_score, scores[ni * n + nj]);
                if (ni == n - 1 && nj == n - 1) {
                    return new_score;
                }

                scores[ni * n + nj] = -1;
                heap.push({new_score, static_cast<int16_t>(ni), static_cast<int16_t>(nj)});
            }
        }

        return 0;
    }
};
