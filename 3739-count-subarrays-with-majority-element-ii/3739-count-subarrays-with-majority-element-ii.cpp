class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> count(2 * n + 1, 0);
        int base = n;
        count[base] = 1;
        
        long long total_subarrays = 0;
        int running_sum = 0;
        long long valid_prefix_count = 0;
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                valid_prefix_count += count[running_sum + base];
                running_sum++;
            } else {
                running_sum--;
                valid_prefix_count -= count[running_sum + base];
            }
            
            total_subarrays += valid_prefix_count;
            count[running_sum + base]++;
        }
        
        return total_subarrays;
    }
};