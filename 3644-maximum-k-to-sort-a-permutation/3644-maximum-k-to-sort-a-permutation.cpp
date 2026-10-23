class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1; 
        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] != i) {
                ans &= nums[i];
            }
        }

        return max(ans, 0); 
    }
};