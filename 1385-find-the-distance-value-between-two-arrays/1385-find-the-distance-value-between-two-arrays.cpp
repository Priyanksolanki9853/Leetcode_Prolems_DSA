class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count = 0;

        for (int x : arr1) {
            auto it = lower_bound(arr2.begin(), arr2.end(), x); // first element >= x
            bool ok = true;

            if (it != arr2.end() && *it - x <= d) ok = false;          // closest on the right
            if (it != arr2.begin() && x - *prev(it) <= d) ok = false;  // closest on the left

            if (ok) count++;
        }

        return count;
    }
};