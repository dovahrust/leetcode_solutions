typedef ptrdiff_t isize;

class Solution {
public:
    static int canCompleteCircuit(const vector<int>& gas, const vector<int>& cost) {
        assert(std::ssize(gas) == std::ssize(cost) && std::ssize(gas) > 0);
        const isize len = std::ssize(gas);
        const int sum_gas = reduce(gas.cbegin(), gas.cend(), 0);
        const int sum_cost = reduce(cost.cbegin(), cost.cend(), 0);
        if (sum_gas < sum_cost) { 
            return -1;
        }

        int diff_sum = 0;
        int selected_idx = 0;

        for (isize i = 0; i < len; i += 1) {
            if (diff_sum < 0) {
                diff_sum = 0;
                selected_idx = i;
            }
            diff_sum += gas[i] - cost[i];
        }

        return static_cast<int>(selected_idx);
    }
};
