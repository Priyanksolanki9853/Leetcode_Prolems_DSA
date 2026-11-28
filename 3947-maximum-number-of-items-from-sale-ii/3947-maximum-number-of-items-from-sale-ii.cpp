class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int maxF = 0;
        int mn = INT_MAX;
        for (auto& it : items) {
            maxF = max(maxF, it[0]);
            mn = min(mn, it[1]);
        }

        vector<int> cnt(maxF + 1, 0), mult(maxF + 1, 0);
        for (auto& it : items) cnt[it[0]]++;
        for (int f = 1; f <= maxF; f++) {
            for (int m = f; m <= maxF; m += f) mult[f] += cnt[m];
        }

        vector<pair<int, long long>> offers; // (price, number of boosted copies g_i)
        for (auto& it : items) {
            long long g = mult[it[0]] - 1;
            if (g > 0 && (long long)it[1] < 2LL * mn) {
                offers.push_back({it[1], g});
            }
        }
        sort(offers.begin(), offers.end());

        long long rem = budget;
        long long boosted = 0;
        for (auto& [price, g] : offers) {
            long long t = min(g, rem / price);
            rem -= t * price;
            boosted += t;
            if (t < g) break; // can't afford this price any more, and later ones cost more
        }

        return (int)(2 * boosted + rem / mn);
    }
};