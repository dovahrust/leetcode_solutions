typedef ptrdiff_t isize;

constexpr int mod_to = 1'000'000'007;

class Solution {
    static inline int mod_pow(const int base, int exp, const int mod_to) {
        int64_t base_i64 = base;
        int64_t res = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                res = (res * base_i64) % mod_to;
            }
            base_i64 = (base_i64 * base_i64) % mod_to;
            exp >>= 1;
        }
        return static_cast<int>(res);
    }

public:
    static int assignEdgeWeights(const vector<vector<int>>& edges) {
        const isize n = std::ssize(edges) + 1;

        auto adj = vector<vector<int>>(n + 1, vector<int>());
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        auto q = deque<int>();
        auto visited = vector<int8_t>(n + 1, 0);
        const int root = 1;
        q.push_back(root);
        visited[root] = 1;
        int level = 0;
        while (!q.empty()) {
            const isize q_len = std::ssize(q);
            for (isize step = 0; step < q_len; step += 1) {
                const int node = q.front();
                q.pop_front();
                for (const auto other_node : adj[node]) {
                    if (visited[other_node] == 0) {
                        visited[other_node] = 1;
                        q.push_back(other_node);
                    }
                }
            }
            level += 1;
        }
        const int edges_max_depth = level - 1;
        if (edges_max_depth  == 0) { return 0; }

        return mod_pow(2, edges_max_depth - 1, mod_to);
    }
};
