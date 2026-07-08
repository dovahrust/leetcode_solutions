static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

int maxChunksToSorted(int* arr, int len)
{
    int stack_len = 0;
    int max = INT_MIN;
    for (int i = 0; i < len; i += 1) {
        max = max_int(max, arr[i]);
        while (stack_len > 0 && arr[stack_len - 1] > arr[i]) {
            stack_len -= 1;
        }
        arr[stack_len] = max;
        stack_len += 1;
    }
    return stack_len;
}
