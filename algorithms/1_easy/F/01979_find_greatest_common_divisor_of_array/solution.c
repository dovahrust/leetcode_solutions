#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static inline int gcd(int a, int b)
{
    while (b != 0) {
        const int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findGCD(const int* nums, const int len)
{
    assert(len > 0 && nums != NULL);
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < len; i += 1) {
        min = MIN(min, nums[i]);
        max = MAX(max, nums[i]);
    }

    return gcd(max, min);
}
