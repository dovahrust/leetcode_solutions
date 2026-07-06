typedef ptrdiff_t isize;

constexpr int64_t mod = 1'000'000'007;

class Solution {
public:
    static int maxPerformance(const int n, const vector<int>& speed, const vector<int>& efficiency, const int k_i32) {
        assert(k_i32 > 0);
        const isize k = k_i32;
        const isize len = std::ssize(speed);
        assert(len == std::ssize(efficiency));

        auto combo = vector<pair<int, int>>(len);

        for (isize i = 0; i < len; i += 1) {
            combo[i] = {efficiency[i], speed[i]};
        }

        ranges::sort(combo, [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        auto heap = priority_queue<int, vector<int>, greater<>>();
        int64_t max_res = 0;
        int64_t sum_speed = 0;

        for (const auto [e, s] : combo) {
            sum_speed += s;
            heap.push(s);
            if (std::ssize(heap) > k) {
                const int s_to_remove = heap.top();
                heap.pop();
                sum_speed -= s_to_remove;
            }

            const int64_t curr = sum_speed * e;
            max_res = std::max(max_res, curr);
        }

        return static_cast<int>(max_res % mod);
    }
};
