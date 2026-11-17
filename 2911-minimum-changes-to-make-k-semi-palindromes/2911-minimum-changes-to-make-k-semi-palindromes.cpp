class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> divs(n + 1);
        for (int d = 1; d <= n; d++) {
            for (int m = 2 * d; m <= n; m += d) {
                divs[m].push_back(d);
            }
        }

        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i + 1;
                int best = INF;

                for (int d : divs[len]) {
                    int changes = 0;
                    int cnt = len / d;
                    for (int r = 0; r < d; r++) {
                        int lo = i + r;
                        int hi = i + r + (cnt - 1) * d;
                        while (lo < hi) {
                            if (s[lo] != s[hi]) changes++;
                            lo += d;
                            hi -= d;
                        }
                    }
                    best = min(best, changes);
                }

                cost[i][j] = best;
            }
        }

        vector<vector<int>> f(k + 1, vector<int>(n + 1, INF));
        f[0][0] = 0;

        for (int p = 1; p <= k; p++) {
            for (int j = 2 * p; j <= n; j++) {
                for (int i = 2 * (p - 1); i <= j - 2; i++) {
                    if (f[p - 1][i] < INF) {
                        f[p][j] = min(f[p][j], f[p - 1][i] + cost[i][j - 1]);
                    }
                }
            }
        }

        return f[k][n];
    }
};