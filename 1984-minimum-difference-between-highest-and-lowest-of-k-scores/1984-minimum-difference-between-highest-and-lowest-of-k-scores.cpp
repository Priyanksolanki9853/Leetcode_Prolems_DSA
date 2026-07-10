class Solution {
public:
    int minimumDifference(vector<int>& arr, int m) {
        int n = arr.size();
        
        if (m == 0 || n < m) return 0;
        
        sort(arr.begin(), arr.end());
        
        int minDiff = INT_MAX;
        
        for (int i = 0; i <= n - m; i++) {
            int currentDiff = arr[i + m - 1] - arr[i];
            minDiff = min(minDiff, currentDiff);
        }
        
        return minDiff;
    }
};