class Solution {
public:
    int atMost(vector<int>& nums, int max_goal) {
        if(max_goal<0) return 0;
        int n = nums.size();
        int left=0;
        int right=0;
        int current=0;
        int length=0;
        int count = 0;
        for (right = 0; right < n; ++right){
            current+=nums[right];
            while(current>max_goal){
                current-=nums[left];
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }
};