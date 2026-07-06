class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& a_next) {
            if (a[0] == a_next[0]) {
                return a[1] > a_next[1];
            }
            return a[0] < a_next[0];
        });

        int remaining_count = 0;
        int max_end = 0;

        for (const auto& interval : intervals) {
            if (interval[1] > max_end) {
                remaining_count++;
                max_end = interval[1];
            }
        }

        return remaining_count;
    }
};