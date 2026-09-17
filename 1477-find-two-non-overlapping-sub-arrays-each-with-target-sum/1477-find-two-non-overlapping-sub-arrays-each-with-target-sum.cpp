class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = INT_MAX / 2;
        vector<int> best(n, INF); 
        int ans = INF;
        int left = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            while (sum > target) {
                sum -= arr[left];
                left++;
            }
            if (sum == target) {
                int len = i - left + 1;
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, best[left - 1] + len);
                }
                best[i] = len;
            }
            if (i > 0) best[i] = min(best[i], best[i - 1]);
        }
        return ans == INF ? -1 : ans;
    }
};