class Solution {
    static inline vector<vector<pair<int, int>>> calc_adj(const span<const vector<int>> edges, const int n) {
        auto res = vector<vector<pair<int, int>>>(static_cast<size_t>(n) + 1uz, vector<pair<int, int>>());
        for (const auto& e : edges) {
            const int u = e[0];
            const int v = e[1];
            const int w = e[2];
            res[u].push_back({v, w});
            res[v].push_back({u, w});
        }
        return res;
    }
public:
    static int minScore(const int n, const vector<vector<int>>& roads) {
        assert(n >= 2);
        auto adj = calc_adj(roads, n);
        auto seen = vector<int8_t>(static_cast<size_t>(n) + 1uz, 0);
        auto q = deque<int>();
        const int root = 1;
        seen[root] = 1;
        q.push_back(root);
        int res = numeric_limits<int>::max();

        while (!q.empty()) {
            const int node = q.front();
            q.pop_front();
            for (const auto [v, w] : adj[node]) {
                res = std::min(res, w);
                if (seen[v] == 0) {
                    seen[v] = 1;
                    q.push_back(v);
                }
            }
        }

        if (!seen[n]) { 
            cerr << "there is no path between 1 and " << n << std::endl;
            exit(0);
        }

        return res;
    }
};
