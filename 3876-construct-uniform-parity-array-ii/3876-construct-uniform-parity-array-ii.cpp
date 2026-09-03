class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = INT_MAX;
        bool hasOdd = false;

        for (int x : nums1) {
            mn = min(mn, x);
            if (abs(x) % 2 != 0) hasOdd = true;
        }

        bool minIsOdd = (abs(mn) % 2 != 0);

        if (minIsOdd) return true;
        return !hasOdd;
    }
};