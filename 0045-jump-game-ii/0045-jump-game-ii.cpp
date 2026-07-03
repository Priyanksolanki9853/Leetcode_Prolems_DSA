class Solution {
public:
    int jump(std::vector<int>& nums) {
        using namespace std;
        
        int jumps = 0;
        int current_end = 0;
        int furthest = 0;
        int n = nums.size();
        
        for (int i = 0; i < n - 1; ++i) {
            furthest = max(furthest, i + nums[i]);
            
            if (i == current_end) {
                jumps++;
                current_end = furthest;
                
                if (current_end >= n - 1) {
                    break;
                }
            }
        }
        
        return jumps;
    }
};