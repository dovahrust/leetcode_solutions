constexpr int max_allowed_price = 10'000;
constexpr int max_allowed_n = 100;
constexpr int max_allowed_flights = ((max_allowed_n * (max_allowed_n - 1)) / 2);
constexpr int inf = numeric_limits<int>::max() / 2;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        assert(k >= 0 && k < n && n <= max_allowed_n && std::ssize(flights) <= max_allowed_flights);
        assert(src >= 0 && src < n && dst >= 0 && dst < n && src != dst);

        auto buff = vector<int>(2 * n, inf);
        auto curr = span<int>(&buff[0], n);
        auto next = span<int>(&buff[n], n);

        curr[src] = 0;
        next[src] = 0;

        for (int stops = 0; stops <= k; stops += 1) {
            for (const auto& f : flights) {
                const int u = f[0];
                const int v = f[1];
                const int w = f[2];
                assert(u >= 0 && u < n && v >=0 && v < n && w >= 1 && w <= max_allowed_price);
                next[v] = std::min(next[v], curr[u] + w);
            }
            auto temp = curr;
            curr = next;
            next = temp;
        }

        return curr[dst] == inf ? -1 : curr[dst];
    }
};
