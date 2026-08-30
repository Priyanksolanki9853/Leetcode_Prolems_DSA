class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minIdx = 0, maxIdx = 0;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIdx]) minIdx = i;
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }
        
        int lo = min(minIdx, maxIdx);
        int hi = max(minIdx, maxIdx);
        
        // Option 1: remove both from the front
        int option1 = hi + 1;
        
        // Option 2: remove both from the back
        int option2 = n - lo;
        
        // Option 3: remove one from front, one from back
        int option3 = (lo + 1) + (n - hi);
        
        return min({option1, option2, option3});
    }
};