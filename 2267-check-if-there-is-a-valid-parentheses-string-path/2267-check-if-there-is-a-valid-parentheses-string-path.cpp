class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // Quick pruning: total path length must be even, and the first/last
        // characters must be '(' and ')' respectively.
        if ((m + n - 1) % 2 != 0 || grid[0][0] == ')' || grid[m-1][n-1] == '(') {
            return false;
        }

        vector<vector<vector<int>>> mem(m, vector<vector<int>>(n, vector<int>(m + n, -1)));
        return dfs(grid, 0, 0, 0, mem);
    }

private:
    // Returns true if there's a valid completion from (i, j) onward,
    // given that k = (count of '(') - (count of ')') so far, INCLUDING (i, j).
    bool dfs(vector<vector<char>>& grid, int i, int j, int k, vector<vector<vector<int>>>& mem) {
        int m = grid.size(), n = grid[0].size();

        k += (grid[i][j] == '(') ? 1 : -1;
        if (k < 0) return false; // too many ')' so far, unrecoverable

        if (i == m - 1 && j == n - 1) {
            return k == 0; // must end perfectly balanced
        }

        if (mem[i][j][k] != -1) return mem[i][j][k];

        bool result = false;
        if (i + 1 < m) result = dfs(grid, i + 1, j, k, mem);
        if (!result && j + 1 < n) result = dfs(grid, i, j + 1, k, mem);

        return mem[i][j][k] = result;
    }
};