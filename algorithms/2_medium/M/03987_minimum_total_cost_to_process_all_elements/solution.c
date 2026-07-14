#define MOD 1000000007

int minimumCost(const int* nums, const int len, const int k)
{
    int64_t sum = 0;
    for (int i = 0; i < len; i += 1) {
        sum += nums[i];
    }
    const int64_t ops = (sum - 1) / k;
    const int64_t costs = (((ops % MOD) * ((ops + 1) % MOD)) / 2) % MOD;
    return (int)costs;
}
