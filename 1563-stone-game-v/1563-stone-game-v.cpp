class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> pre(n + 1, 0);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + stoneValue[i];

        // dp[i][j] = max score Alice can get from subarray [i..j]
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                long long best = 0;
                for (int k = i; k < j; k++) {
                    long long left  = pre[k + 1] - pre[i];       // sum of [i..k]
                    long long right = pre[j + 1] - pre[k + 1];   // sum of [k+1..j]
                    long long score;
                    if (left < right)
                        score = left + dp[i][k];          // right thrown away, left remains
                    else if (left > right)
                        score = right + dp[k + 1][j];      // left thrown away, right remains
                    else
                        score = left + max(dp[i][k], dp[k + 1][j]); // tie, Alice picks better
                    best = max(best, score);
                }
                dp[i][j] = best;
            }
        }

        return (int)dp[0][n - 1];
    }
};