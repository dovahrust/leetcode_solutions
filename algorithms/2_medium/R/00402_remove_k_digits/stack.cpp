typedef ptrdiff_t isize;

class Solution {
public:
    static string removeKdigits(string num, int k) {
        const isize num_len = std::ssize(num);
        assert(num_len > 0);
        isize stack_len = 0;

        for (isize i = 0; i < num_len; i += 1) {
            while (k > 0 && stack_len > 0 && num[stack_len - 1] > num[i]) {
                stack_len -= 1;
                k -= 1;
            }

            if (stack_len == 0 && num[i] == '0') {
                continue;
            }

            num[stack_len] = num[i];
            stack_len += 1;
        }

        stack_len -= std::min(stack_len, static_cast<isize>(k));

        if (stack_len == 0) {
            num[stack_len] = '0';
            stack_len += 1;
        }

        num.resize(stack_len);

        return num;
    }
};
