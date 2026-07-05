#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        vector<vector<int>> max_sum(n, vector<int>(n, -1));
        vector<vector<int>> path_count(n, vector<int>(n, 0));
        
        max_sum[0][0] = 0;
        path_count[0][0] = 1;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((r == 0 && c == 0) || board[r][c] == 'X') {
                    continue;
                }
                
                int current_val = 0;
                if (isdigit(board[r][c])) {
                    current_val = board[r][c] - '0';
                }
                
                int best_sum = -1;
                int ways = 0;
                
                int directions[3][2] = {{r - 1, c}, {r, c - 1}, {r - 1, c - 1}};
                
                for (int i = 0; i < 3; ++i) {
                    int pr = directions[i][0];
                    int pc = directions[i][1];
                    
                    if (pr >= 0 && pr < n && pc >= 0 && pc < n && max_sum[pr][pc] != -1) {
                        if (max_sum[pr][pc] > best_sum) {
                            best_sum = max_sum[pr][pc];
                            ways = path_count[pr][pc];
                        } else if (max_sum[pr][pc] == best_sum) {
                            ways = (ways + path_count[pr][pc]) % MOD;
                        }
                    }
                }
                
                if (best_sum != -1) {
                    max_sum[r][c] = best_sum + current_val;
                    path_count[r][c] = ways;
                }
            }
        }
        
        int final_sum = max_sum[n-1][n-1];
        int final_ways = path_count[n-1][n-1];
        
        if (final_sum == -1) {
            return {0, 0};
        }
        
        return {final_sum, final_ways};
    }
};