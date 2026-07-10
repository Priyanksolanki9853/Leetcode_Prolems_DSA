class Solution {
public:
    int rob(vector<int>& nums) {
        int rob_prev2=0;
        int rob_prev1=0;
        for (int money : nums) {
            int current_max = max(rob_prev2 + money, rob_prev1);
            
            rob_prev2 = rob_prev1;
            rob_prev1 = current_max;
        }
        return rob_prev1;
    }
};