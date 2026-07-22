class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {false};
        bool cols[9][9] = {false};
        bool boxes[9][9] = {false};
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] != '.') {
                    int num = board[r][c] - '1'; 
                    int box_idx = (r / 3) * 3 + (c / 3);
                    if (rows[r][num] || cols[c][num] || boxes[box_idx][num]) {
                        return false;
                    }
                    rows[r][num] = true;
                    cols[c][num] = true;
                    boxes[box_idx][num] = true;
                }
            }
        }
        return true;
    }
};