class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0); // dp[r] = # subarrays ending at previous index with product % k == r

        for (int num : nums) {
            vector<long long> next(k, 0);
            int value = num % k;

            next[value]++; // new subarray consisting of just this element

            // extend every subarray that ended at the previous index
            for (int r = 0; r < k; r++) {
                if (dp[r] == 0) continue;
                int newRemainder = (r * value) % k;
                next[newRemainder] += dp[r];
            }

            for (int r = 0; r < k; r++) result[r] += next[r];
            dp = move(next);
        }

        return result;
    }
};