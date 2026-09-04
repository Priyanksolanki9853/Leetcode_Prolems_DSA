class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int maxLeft = nums[0];
            for (int a = 0; a <= i; a++) {
                maxLeft = max(maxLeft, nums[a]);
            }
            int minRight = nums[i];
            for (int b = i; b < n; b++) {
                minRight = min(minRight, nums[b]);
            }
            if (maxLeft - minRight <= k) {
                return i;
            }
        }
        return -1;
    }
};