class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        ranges::sort(tasks, [](const auto& a, const auto& b) {
            return (a[0] - a[1]) <  (b[0] - b[1]);
        });

        int total_energy = 0;
        int remain = 0;

        for (const auto& t : tasks) {
            const int actual = t[0];
            const int minimum = t[1];
            assert(actual <= minimum);
            if (minimum > remain) {
                total_energy += minimum - remain;
                remain = minimum;
            }
            remain -= actual;
        }

        return total_energy;
    }
};
