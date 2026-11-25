class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> sa(n), rk(n), tmp(n);
        for (int i = 0; i < n; i++) {
            rk[i] = lower_bound(vals.begin(), vals.end(), nums[i]) - vals.begin();
        }
        iota(sa.begin(), sa.end(), 0);

        for (int k = 1;; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = a + k < n ? rk[a + k] : -1;
                int rb = b + k < n ? rk[b + k] : -1;
                return ra < rb;
            };
            sort(sa.begin(), sa.end(), cmp);

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            rk = tmp;
            if (rk[sa[n - 1]] == n - 1) break;
        }

        vector<int> lcp(max(n - 1, 0), 0);
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rk[i] > 0) {
                int j = sa[rk[i] - 1];
                while (i + h < n && j + h < n && nums[i + h] == nums[j + h]) h++;
                lcp[rk[i] - 1] = h;
                if (h > 0) h--;
            } else {
                h = 0;
            }
        }

        int ans = n;
        for (int p = 0; p < n; p++) {
            int i = sa[p];
            int m = 0;
            if (p > 0) m = max(m, lcp[p - 1]);
            if (p < n - 1) m = max(m, lcp[p]);
            int L = m + 1;
            if (L <= n - i) ans = min(ans, L);
        }

        return ans;
    }
};