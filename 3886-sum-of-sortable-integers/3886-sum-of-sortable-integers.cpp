class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;
            int prevMax = INT_MIN;

            for (int s = 0; s < n && ok; s += k) {
                int descents = 0;
                int mn = INT_MAX, mx = INT_MIN;

                for (int i = 0; i < k; i++) {
                    int cur = nums[s + i];
                    int nxt = nums[s + (i + 1) % k]; 
                    if (cur > nxt) descents++;
                    mn = min(mn, cur);
                    mx = max(mx, cur);
                }
                if (descents > 1 || mn < prevMax) ok = false;
                prevMax = mx;
            }

            if (ok) ans += k;
        }

        return ans;
    }
};