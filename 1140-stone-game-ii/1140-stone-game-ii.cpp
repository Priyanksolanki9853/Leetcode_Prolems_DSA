class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // suffix_sum[i] stores the sum of stones from index i to the end
        vector<int> suffix_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        }
        
        // dp[i][M] 
        // We use n + 1 for M because M can grow up to n (if we take all remaining piles).
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        
        // Fill DP table from back to front (bottom-up approach)
        for (int i = n - 1; i >= 0; --i) {
            for (int M = 1; M <= n; ++M) {
                // If the player can take all the remaining piles, they should.
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix_sum[i];
                } else {
                    // Try all possible valid moves (taking X piles)
                    for (int X = 1; X <= 2 * M; ++X) {
                        dp[i][M] = max(dp[i][M], suffix_sum[i] - dp[i + X][max(M, X)]);
                    }
                }
            }
        }
        
        // Return the max stones Alice can get starting at index 0 with M = 1
        return dp[0][1];
    }
};