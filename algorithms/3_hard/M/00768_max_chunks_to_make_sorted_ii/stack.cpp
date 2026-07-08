typedef ptrdiff_t isize;

class Solution {
public:
    static int maxChunksToSorted(vector<int>& arr) {
        const isize len = std::ssize(arr);
        isize stack_len = 0;
        int max = numeric_limits<int>::min();
        for (isize i = 0; i < len; i += 1) {
            max = std::max(max, arr[i]);
            while (stack_len > 0 && arr[stack_len - 1] > arr[i]) {
                stack_len -= 1;
            }
            arr[stack_len] = max;
            stack_len += 1;
        }
        assert(stack_len <= numeric_limits<int>::max());
        return static_cast<int>(stack_len);
    }
};
