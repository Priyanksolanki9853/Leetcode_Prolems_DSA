class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        map<int, vector<int>> diagonals;
        
        for (int r = nums.size() - 1; r >= 0; --r) {
            for (int c = 0; c < nums[r].size(); ++c) {
                diagonals[r + c].push_back(nums[r][c]);
            }
        }
        
        vector<int> result;
        for (auto& pair : diagonals) {
            result.insert(result.end(), pair.second.begin(), pair.second.end());
        }
        
        return result;
    }
};