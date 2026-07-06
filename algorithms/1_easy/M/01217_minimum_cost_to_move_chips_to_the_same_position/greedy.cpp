class Solution {
public:
    static int minCostToMoveChips(const vector<int>& position) {
        assert(std::ssize(position) <= 100);
        int cnt[2] = { 0 };

        for (const int p : position) {
            cnt[(p & 1)] += 1;
        }

        return std::min(cnt[0], cnt[1]);
    }
};
