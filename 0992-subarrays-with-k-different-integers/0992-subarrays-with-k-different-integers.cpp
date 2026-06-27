class Solution {
public:
    int atMost(vector<int>& nums, int max_k) {
        if (max_k < 0) return 0;
        
        unordered_map<int, int> count;
        int left = 0;
        int total_subarrays = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            if (count[nums[right]] == 0) {
                max_k--;
            }
            count[nums[right]]++;
            
            while (max_k < 0) {
                count[nums[left]]--;
                if (count[nums[left]] == 0) {
                    max_k++;
                }
                left++;
            }
            
            total_subarrays += (right - left + 1);
        }
        
        return total_subarrays;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
};