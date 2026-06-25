class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int l = 0;
        int odd_count = 0;
        int current_subarrays = 0;
        int total_nice_subarrays = 0;
        for (int r = 0; r < nums.size(); ++r) {
            if (nums[r] % 2 != 0) {
                odd_count++;
                current_subarrays = 0;
            } 
            while (odd_count == k) {
                current_subarrays++;
                if (nums[l] % 2 != 0) {
                    odd_count--;
                }
                l++;
            }
            total_nice_subarrays += current_subarrays;
        }
        return total_nice_subarrays;
    }
};