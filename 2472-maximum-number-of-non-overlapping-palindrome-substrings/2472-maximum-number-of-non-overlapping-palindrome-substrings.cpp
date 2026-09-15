class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        if (k > n) return 0;
        vector<int> dp(n + 1, 0);
        auto isPalindrome = [&](int l, int r) { 
            while (l < r) {
                if (s[l] != s[r]) return false;
                l++; r--;
            }
            return true;
        };
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1]; 
            if (i >= k && isPalindrome(i - k, i - 1)) {
                dp[i] = max(dp[i], dp[i - k] + 1);
            }
            else if (i >= k + 1 && isPalindrome(i - k - 1, i - 1)) {
                dp[i] = max(dp[i], dp[i - k - 1] + 1);
            }
        }
        return dp[n];
    }
};