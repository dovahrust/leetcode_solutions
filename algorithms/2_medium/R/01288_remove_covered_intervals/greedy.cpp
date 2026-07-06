typedef ptrdiff_t isize;

class Solution {
public:
    static int removeCoveredIntervals(vector<vector<int>>& intervals) {
        ranges::sort(intervals, [](const auto& a, const auto& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }

            return a[0] < b[0];
        });

        const isize len = std::ssize(intervals);
        isize invalids_cnt = 0;
        int prev_end = intervals[0][1];

        for (isize i = 1; i < len; ++i) {
            if (intervals[i][1] <=  prev_end) {
                invalids_cnt += 1;
            } else {
                prev_end = intervals[i][1];
            }
        }

        return static_cast<int>(len - invalids_cnt);
    }
};
