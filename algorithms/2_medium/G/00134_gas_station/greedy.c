typedef ptrdiff_t isize;

static inline int reduce(const int* restrict arr, const isize len)
{
    int sum = 0;
    for (isize i = 0; i < len; i += 1) {
        sum += arr[i];
    }
    return sum;
}

int canCompleteCircuit(int* gas, int gas_len, int* cost, int cost_len)
{
    assert(gas_len == cost_len && gas_len > 0 && gas != NULL && cost != NULL);
    const isize len = gas_len;
    const int sum_gas = reduce(gas, len);
    const int sum_cost = reduce(cost, len);
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

    return (int)selected_idx;
}
