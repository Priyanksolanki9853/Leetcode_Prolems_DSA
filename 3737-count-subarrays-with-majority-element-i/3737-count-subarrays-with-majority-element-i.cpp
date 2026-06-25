class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> prefix_sums(n + 1, 0);
        int current_sum = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                current_sum += 1;
            } else {
                current_sum -= 1;
            }
            prefix_sums[i + 1] = current_sum;
        }
        int count = 0;
        for (int j = 1; j <= n; ++j) {
            for (int i = 0; i < j; ++i) {
                if (prefix_sums[j] > prefix_sums[i]) {
                    count++;
                }
            }
        }
        return count;
    }
};