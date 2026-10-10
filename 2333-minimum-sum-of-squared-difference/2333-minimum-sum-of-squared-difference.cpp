class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<long long> d(n);
        for (int i = 0; i < n; i++) d[i] = abs(nums1[i] - nums2[i]);
        sort(d.rbegin(), d.rend()); // descending

        long long k = (long long)k1 + k2;
        long long level = d[0]; // current top level
        long long cnt = 1;      // number of elements currently at 'level'
        int idx = 1;            // next element not yet merged into the group
        long long r = 0;        // elements that end up one below 'level'

        while (true) {
            while (idx < n && d[idx] == level) { cnt++; idx++; }

            long long nextLevel = (idx < n) ? d[idx] : 0;
            long long cost = cnt * (level - nextLevel);

            if (k >= cost) {
                k -= cost;
                level = nextLevel;
                if (level == 0) break; // everything is flattened to 0
            } else {
                long long q = k / cnt;
                r = k % cnt;
                level -= q;
                break;
            }
        }

        long long ans = r * (level - 1) * (level - 1) + (cnt - r) * level * level;
        for (int j = idx; j < n; j++) ans += d[j] * d[j]; // untouched smaller elements
        return ans;
    }
};