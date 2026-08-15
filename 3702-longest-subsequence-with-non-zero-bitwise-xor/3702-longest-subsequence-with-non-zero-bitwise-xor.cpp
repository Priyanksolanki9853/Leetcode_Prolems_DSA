class Solution {
public:
    int longestSubsequence(std::vector<int>& nums) {
        int total_xor = 0;
        bool all_zero = true;
        
        for (int num : nums) {
            total_xor ^= num;
            if (num != 0) {
                all_zero = false;
            }
        }
        if (all_zero) {
            return 0;
        }
        if (total_xor != 0) {
            return nums.size();
        }
        return nums.size() - 1;
    }
};