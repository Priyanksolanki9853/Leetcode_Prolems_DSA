#include <iostream>
#include <vector>
#include <queue>

struct State {
    int r, c, h;
};

class Solution {
public:
    bool findSafeWalk(std::vector<std::vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        std::vector<std::vector<int>> max_health(m, std::vector<int>(n, -1));
        std::queue<State> q;
        
        int start_health = health - grid[0][0];
        if (start_health <= 0) return false;
        
        q.push({0, 0, start_health});
        max_health[0][0] = start_health;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            State curr = q.front();
            q.pop();
            
            if (curr.h < max_health[curr.r][curr.c]) continue;
            if (curr.r == m - 1 && curr.c == n - 1 && curr.h >= 1) return true;
            
            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int next_health = curr.h - grid[nr][nc];
                    if (next_health > max_health[nr][nc] && next_health >= 1) {
                        max_health[nr][nc] = next_health;
                        q.push({nr, nc, next_health});
                    }
                }
            }
        }
        
        return max_health[m - 1][n - 1] >= 1;
    }
};