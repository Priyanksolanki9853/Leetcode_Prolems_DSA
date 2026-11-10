class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        const int INF = INT_MAX / 2;

        int f1 = 0;
        int f2 = INF;
        int f3 = INF;

        for (int i = 1; i <= n; i++) {
            int best = min({f1 + 1, f2 + 4, f3 + 9});
            int cur = costs[i - 1] + best;
            f3 = f2;
            f2 = f1;
            f1 = cur;
        }

        return f1;
    }
};