class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;
        int bit_length = 0;
        int temp = n;
        while (temp > 0) {
            bit_length++;
            temp >>= 1;
        }
        return 1 <<bit_length;
    }
};