class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> R(m, vector<int>(n, 0)), D(m, vector<int>(n, 0));
        R[0][0] = 1; 
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int landed = (R[i][j] + D[i][j]) % MOD;
                    if (i == m - 1 && j == n - 1) return landed;

                    if (j + 1 < n) R[i][j + 1] = (R[i][j + 1] + landed) % MOD; 
                    if (i + 1 < m) D[i + 1][j] = (D[i + 1][j] + landed) % MOD; 
                } else {
                    if (i + 1 < m) D[i + 1][j] = (D[i + 1][j] + R[i][j]) % MOD;
                    if (j + 1 < n) R[i][j + 1] = (R[i][j + 1] + D[i][j]) % MOD;
                }
            }
        }

        return 0; 
    }
};