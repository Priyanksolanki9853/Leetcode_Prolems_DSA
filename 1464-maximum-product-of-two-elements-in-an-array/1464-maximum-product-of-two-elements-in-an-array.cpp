class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product=0;
        int n=nums.size();
        int i=0;
        int j=0;
        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                int current_product = (nums[i] - 1) * (nums[j] - 1);
                max_product = max(max_product, current_product);
            }
        }
        return max_product;
    }
};