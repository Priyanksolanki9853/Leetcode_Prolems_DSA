class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const int MX = 1024; 
        vector<vector<bitset<MX>>> f(m, vector<bitset<MX>>(n));
        f[0][0][grid[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                bitset<MX> src; 
                if (i > 0) src |= f[i - 1][j];
                if (j > 0) src |= f[i][j - 1];

                int x = grid[i][j];
                for (int k = 0; k < MX; k++) {
                    if (src[k]) f[i][j][k ^ x] = 1;
                }
            }
        }

        for (int k = 0; k < MX; k++) {
            if (f[m - 1][n - 1][k]) return k;
        }
        return -1; 
    }
};