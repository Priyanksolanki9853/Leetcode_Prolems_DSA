class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // ---- Step 1: cost[s] = min operations to equalize window nums[s..s+x-1] ----
        multiset<int> lo, hi; // lo holds the smaller half, hi the larger half
        long long sumLo = 0, sumHi = 0;

        auto rebalance = [&]() {
            while (lo.size() > hi.size() + 1) {
                auto it = prev(lo.end());
                int v = *it;
                lo.erase(it);
                sumLo -= v;
                hi.insert(v);
                sumHi += v;
            }
            while (lo.size() < hi.size()) {
                auto it = hi.begin();
                int v = *it;
                hi.erase(it);
                sumHi -= v;
                lo.insert(v);
                sumLo += v;
            }
        };
        auto add = [&](int v) {
            if (lo.empty() || v <= *lo.rbegin()) {
                lo.insert(v);
                sumLo += v;
            } else {
                hi.insert(v);
                sumHi += v;
            }
            rebalance();
        };
        auto remove = [&](int v) {
            if (v <= *lo.rbegin()) {
                lo.erase(lo.find(v));
                sumLo -= v;
            } else {
                hi.erase(hi.find(v));
                sumHi -= v;
            }
            rebalance();
        };

        vector<long long> cost(n - x + 1);
        for (int i = 0; i < n; i++) {
            add(nums[i]);
            if (i >= x) remove(nums[i - x]);
            if (i >= x - 1) {
                long long med = *lo.rbegin();
                cost[i - x + 1] = med * (long long)lo.size() - sumLo
                                + sumHi - med * (long long)hi.size();
            }
        }

        // ---- Step 2: choose k non-overlapping windows with minimum total cost ----
        const long long INF = LLONG_MAX / 4;
        vector<vector<long long>> f(k + 1, vector<long long>(n + 1, INF));
        for (int i = 0; i <= n; i++) f[0][i] = 0;

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {
                f[j][i] = f[j][i - 1];                       // skip element i-1
                if (i >= x && f[j - 1][i - x] < INF) {       // window ending at i-1
                    f[j][i] = min(f[j][i], f[j - 1][i - x] + cost[i - x]);
                }
            }
        }

        return f[k][n];
    }
};