int countValidSubarrays(int* nums, int len, int x)
{
    assert(nums != NULL && len > 0 && x >= 1 && x <= 9);
    int cnt = 0;

    for (int i = 0; i < len; i += 1) {
        int64_t sum = 0;
        for (int j = i; j < len; j += 1) {
            sum += nums[j];
            const int64_t lowest_dig = sum % 10;
            if (lowest_dig == x) {
                int64_t temp = sum;
                while (temp >= 10) {
                    temp /= 10;
                }
                const int64_t highest_dig = temp;
                if (highest_dig == x) {
                    cnt += 1;
                }
            }
        }
    }

    return cnt;
}
