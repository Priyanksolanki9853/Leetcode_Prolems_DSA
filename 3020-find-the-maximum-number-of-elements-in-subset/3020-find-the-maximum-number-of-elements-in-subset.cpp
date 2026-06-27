class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        for (int num : nums) {
            count[num]++;
        }

        int max_len = 1;

        if (count.count(1)) {
            int ones = count[1];
            max_len = max(max_len, ones % 2 == 0 ? ones - 1 : ones);
        }

        unordered_map<long long, int> dp;
        vector<long long> unique_nums;
        for (auto& pair : count) {
            if (pair.first > 1) {
                unique_nums.push_back(pair.first);
            }
        }
        sort(unique_nums.rbegin(), unique_nums.rend());

        for (long long x : unique_nums) {
            long long target = x * x;
            if (count[x] >= 2 && dp.count(target)) {
                dp[x] = dp[target] + 2;
            } else {
                dp[x] = 1;
            }
            max_len = max(max_len, dp[x]);
        }

        return max_len;
    }
};