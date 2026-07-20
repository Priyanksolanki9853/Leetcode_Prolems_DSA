#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total_elements = m * n;
        
        // If k is larger than the total number of elements, we only need the remainder
        k = k % total_elements;
        
        // If k is 0 after modulo, the grid remains unchanged
        if (k == 0) return grid;
        
        // Create a new grid of the same dimensions to store the result
        vector<vector<int>> result(m, vector<int>(n));
        
        // Map elements to their new positions
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Convert current 2D index to 1D index
                int current_1d_index = i * n + j;
                
                // Calculate the new 1D index after shifting k times
                int next_1d_index = (current_1d_index + k) % total_elements;
                
                // Convert the new 1D index back to 2D coordinates
                int next_i = next_1d_index / n;
                int next_j = next_1d_index % n;
                
                // Place the element in the new grid
                result[next_i][next_j] = grid[i][j];
            }
        }
        
        return result;
    }
};