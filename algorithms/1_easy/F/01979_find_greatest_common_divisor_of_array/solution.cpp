class Solution {
public:
    static int findGCD(const vector<int>& nums) {
        int min = numeric_limits<int>::max();
        int max = numeric_limits<int>::min();

        for (const int num : nums) {
            min = std::min(min, num);
            max = std::max(max, num);
        }

        return gcd(max, min);
    }
};
