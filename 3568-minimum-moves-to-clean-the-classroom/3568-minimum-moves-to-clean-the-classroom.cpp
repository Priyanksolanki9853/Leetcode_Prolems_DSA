class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int,int>> litterPos;
        vector<vector<int>> litterIdx(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                char c = classroom[i][j];
                if (c == 'S') { sr = i; sc = j; }
                else if (c == 'L') {
                    litterIdx[i][j] = litterPos.size();
                    litterPos.push_back({i, j});
                }
            }
        }

        int litterCount = litterPos.size();
        int fullMask = (litterCount == 0) ? 0 : (1 << litterCount) - 1;

        if (fullMask == 0) return 0; // no litter to collect

        // best[r][c][mask] = maximum energy seen for this state
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << litterCount, -1))
        );

        int startMask = 0; // 'S' cell is not litter itself
        best[sr][sc][startMask] = energy;

        queue<tuple<int,int,int>> q; // r, c, mask
        q.push({sr, sc, startMask});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int k = 0; k < levelSize; k++) {
                auto [r, c, mask] = q.front();
                q.pop();

                int e = best[r][c][mask];

                if (mask == fullMask) return moves;

                if (e <= 0) continue; // no energy left to move, and not on 'R' (handled below anyway)

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    if (classroom[nr][nc] == 'X') continue;

                    int newE = e - 1;
                    if (classroom[nr][nc] == 'R') newE = energy;

                    int newMask = mask;
                    if (classroom[nr][nc] == 'L' && litterIdx[nr][nc] != -1) {
                        newMask |= (1 << litterIdx[nr][nc]);
                    }

                    if (newE > best[nr][nc][newMask]) {
                        best[nr][nc][newMask] = newE;
                        q.push({nr, nc, newMask});
                    }
                }
            }
            moves++;
        }

        return -1;
    }
};