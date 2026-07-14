class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int maxNum = *max_element(nums.begin(), nums.end());
        
        // dp[g1][g2] stores the number of pairs with GCD g1 and g2
        vector<vector<int>> dp(maxNum + 1, vector<int>(maxNum + 1, 0));
        dp[0][0] = 1; // Base case: both subsequences are empty
        
        for (int x : nums) {
            // Create a copy to preserve 'skip' transitions implicitly
            vector<vector<int>> next_dp = dp;
            
            for (int g1 = 0; g1 <= maxNum; ++g1) {
                for (int g2 = 0; g2 <= maxNum; ++g2) {
                    if (dp[g1][g2] == 0) continue;
                    
                    // Option 1: Add x to the first subsequence
                    int ng1 = std::gcd(g1, x);
                    next_dp[ng1][g2] = (next_dp[ng1][g2] + dp[g1][g2]) % MOD;
                    
                    // Option 2: Add x to the second subsequence
                    int ng2 = std::gcd(g2, x);
                    next_dp[g1][ng2] = (next_dp[g1][ng2] + dp[g1][g2]) % MOD;
                }
            }
            dp = move(next_dp);
        }
        
        // Sum all valid states where both subsequences are non-empty (g >= 1) and have equal GCD
        long long totalPairs = 0;
        for (int g = 1; g <= maxNum; ++g) {
            totalPairs = (totalPairs + dp[g][g]) % MOD;
        }
        
        return totalPairs;
    }
};