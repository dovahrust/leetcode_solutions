typedef  ptrdiff_t isize;
typedef  pair<int, int> DegCntUsedCnt;

class Solution {
    static inline vector<vector<pair<int, int>>> calc_adj(span<const vector<int>> edges, vector<bool>& online) {
        auto res = vector<vector<pair<int, int>>> (online.size(), vector<pair<int, int>>());
        for (const auto& e : edges) {
            const int u = e[0];
            const int v = e[1];
            const int cost = e[2];
            assert(u < std::ssize(online) && v < std::ssize(online) && cost >= 0);
            if (online[u] && online[v]) {
                res[u].push_back({v, cost});
            }
        }
        return res;
    }

    static inline vector<DegCntUsedCnt> calc_deg(span<vector<pair<int, int>>> adj) {
        auto res = vector<DegCntUsedCnt>(adj.size(), {0, 0});
        for (const auto& a : adj) {
            for (const auto [v, _] : a) {
                res[v].first += 1;
            }
        }

        const isize len = std::ssize(adj);
        for (isize u = 1; u < len; u += 1) {
            if (res[u].first == 0) {
                for (const auto [v, _] : adj[u]) {
                    res[v].first -= 1;
                }
            }
        }

        return res;
    }

    static bool check(span<vector<pair<int, int>>> adj, deque<int>& q, span<int64_t> costs, span<DegCntUsedCnt> deg, int mid, int target, int64_t k) {
        for (auto& c : costs) { c = numeric_limits<int64_t>::max() / 2; }
        for (auto& d : deg) { d.second = 0; }
        q.clear();
        q.push_back(0);
        costs[0] = 0;

        while (!q.empty()) {
            const int node = q.front();
            q.pop_front();
            const int64_t total_cost = costs[node];

            for (const auto [v, cost] : adj[node]) {
                deg[v].second += 1;
                if (deg[v].first == deg[v].second) {
                    q.push_back(v);
                }
                if (cost >= mid) {
                    costs[v] = std::min(costs[v], total_cost + cost);
                }
            }
        }

        return costs[target] <= k;
    }

public:
    static int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        if (edges.empty()) { return -1; }

        int lo = numeric_limits<int>::max();;
        int hi = 0;
        for (const auto& e : edges) {
            lo = std::min(lo, e[2]);
            hi = std::max(hi, e[2]);
        }

        const int target = static_cast<int>(std::ssize(online)) - 1;
        auto q = deque<int>();
        auto costs = vector<int64_t>(online.size(), 0);
        auto adj = calc_adj(edges, online);
        auto deg = calc_deg(adj);

        if (!check(adj, q, costs, deg, lo, target, k)) {
            return -1;
        }

        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (check(adj, q, costs, deg, mid, target, k)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return hi;
    }
};
