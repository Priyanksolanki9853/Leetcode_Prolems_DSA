class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        long long MOD = 1e9 + 7;

        if (m <= 1) return 0;
        if (n == 1) return m;

        vector<long long> up(m, 0), down(m, 0);

        for (int i = 0; i < m; ++i) {
            up[i] = i; 
            down[i] = (m - 1 - i); 
        }

        for (int len = 3; len <= n; ++len) {
            vector<long long> next_up(m, 0), next_down(m, 0);
            
            long long prefix_sum_down = 0;
            for (int i = 0; i < m; ++i) {
                next_up[i] = prefix_sum_down;
                prefix_sum_down = (prefix_sum_down + down[i]) % MOD;
            }

            long long suffix_sum_up = 0;
            for (int i = m - 1; i >= 0; --i) {
                next_down[i] = suffix_sum_up;
                suffix_sum_up = (suffix_sum_up + up[i]) % MOD;
            }

            up = std::move(next_up);
            down = std::move(next_down);
        }

        long long total = 0;
        for (int i = 0; i < m; ++i) {
            total = (total + up[i] + down[i]) % MOD;
        }

        return total;
    }
};