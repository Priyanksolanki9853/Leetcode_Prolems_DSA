class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        int countOdd = 0;
        for (int x : nums1) {
            if (abs(x) % 2 != 0) countOdd++;
        }
        int countEven = n - countOdd;

        bool targetEvenFeasible = (countOdd == 0 || countOdd >= 2);
        bool targetOddFeasible  = (countEven == 0 || countOdd >= 1);

        return targetEvenFeasible || targetOddFeasible;
    }
};