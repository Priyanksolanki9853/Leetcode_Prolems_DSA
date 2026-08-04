class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) { // Fixed function name here
        int min_val = 101; 
        int max_val = 0;
        bool present[101] = {false};
        
        // Find boundaries and mark present numbers in a single pass
        for (int num : nums) {
            if (num < min_val) min_val = num;
            if (num > max_val) max_val = num;
            present[num] = true;
        }
        
        vector<int> missing;
        // Iterate through the expected range
        for (int i = min_val + 1; i < max_val; ++i) {
            if (!present[i]) {
                missing.push_back(i);
            }
        }
        
        return missing;
    }
};