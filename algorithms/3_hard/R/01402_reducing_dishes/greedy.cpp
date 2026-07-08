typedef ptrdiff_t isize;

class Solution {
public:
    static int maxSatisfaction(vector<int>& satisfaction) {
        assert(std::ssize(satisfaction) >= 1 && std::ssize(satisfaction) <= 500);
        assert(all_of(satisfaction.cbegin(), satisfaction.cend(), [](const auto& a) { 
            return -1000 <= a && a <= 1000;
        }));

        ranges::sort(satisfaction, [](const auto& a, const auto& b) {
            return a > b;
        });

        int res = 0;
        int curr_sum = 0;

        for (const int s : satisfaction) {
            curr_sum += s;
            const int new_res = res + curr_sum;

            if (new_res < res) {
                break;
            }

            res = new_res;
        }

        return res;
    }
};
