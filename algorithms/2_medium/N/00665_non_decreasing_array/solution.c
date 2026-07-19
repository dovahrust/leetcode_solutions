static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

static inline bool forward(const int* nums, const int len)
{
    int cnt = 0;
    int max = INT_MIN;
    for (int i = 0; i < len; i += 1) {
        max = max_int(max, nums[i]);
        if (nums[i] < max) {
            cnt += 1;
            if (cnt >= 2) {
                return false;
            }
        }
    }
    return true;
}

static inline bool backward(const int* nums, const int len)
{
    int cnt = 0;
    int min = INT_MAX;
    for (int i = len - 1; i >= 0; i -= 1) {
        min = min_int(min, nums[i]);
        if (nums[i] > min) {
            cnt += 1;
            if (cnt >= 2) {
                return false;
            }
        }
    }
    return true;
}

bool checkPossibility(const int* nums, const int len)
{
    return forward(nums, len) || backward(nums, len);
}
