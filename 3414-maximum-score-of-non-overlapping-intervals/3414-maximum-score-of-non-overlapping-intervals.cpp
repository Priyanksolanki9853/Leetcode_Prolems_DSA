struct T {
    long weight;
    vector<int> selected;
};

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& input) {
        vector<Interval> intervals;
        for (int i = 0; i < input.size(); ++i)
            intervals.emplace_back(input[i][0], input[i][1], input[i][2], i);
        sort(intervals.begin(), intervals.end());
        vector<vector<T>> memo(intervals.size(), vector<T>(5));
        return dp(intervals, memo, 0, 4).selected;
    }

private:
    using Interval = tuple<int, int, int, int>; // (left, right, weight, originalIndex)

    T dp(const vector<Interval>& intervals, vector<vector<T>>& memo, int i, int quota) {
        if (i == (int)intervals.size() || quota == 0)
            return T();
        if (memo[i][quota].weight > 0)
            return memo[i][quota];

        T skip = dp(intervals, memo, i + 1, quota);

        auto [l, r, weight, originalIndex] = intervals[i];
        int j = findFirstGreater(intervals, i + 1, r);
        T nextRes = dp(intervals, memo, j, quota - 1);

        vector<int> newSelected = nextRes.selected;
        newSelected.push_back(originalIndex);
        sort(newSelected.begin(), newSelected.end());
        T pick(static_cast<long>(weight) + nextRes.weight, newSelected);

        return memo[i][quota] =
            (pick.weight > skip.weight ||
             (pick.weight == skip.weight && pick.selected < skip.selected))
                ? pick : skip;
    }

    // Finds the first interval (from startFrom) whose left endpoint > rightBoundary.
    int findFirstGreater(const vector<Interval>& intervals, int startFrom, int rightBoundary) {
        int l = startFrom, r = intervals.size();
        while (l < r) {
            int m = (l + r) / 2;
            if (get<0>(intervals[m]) > rightBoundary) r = m;
            else l = m + 1;
        }
        return l;
    }
};