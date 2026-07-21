class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";
        
        vector<int> ones;
        vector<int> zeros;
        
        int count = 0;
        char current = '1';
        
        for (char c : t) {
            if (c == current) {
                count++;
            } else {
                if (current == '1') {
                    ones.push_back(count);
                    current = '0';
                } else {
                    zeros.push_back(count);
                    current = '1';
                }
                count = 1;
            }
        }
        
        if (current == '1') {
            ones.push_back(count);
        } else {
            zeros.push_back(count);
        }
        
        int initial_ones = 0;
        for (int x : ones) {
            initial_ones += x;
        }
        initial_ones -= 2; 
        
        if (ones.size() < 3) {
            return initial_ones;
        }
        
        int max_z = 0;
        for (int z : zeros) {
            max_z = max(max_z, z);
        }
        
        int max_gain = 0;
        
        for (int i = 1; i < ones.size() - 1; i++) {
            int gain1 = zeros[i - 1] + zeros[i];
            int gain2 = max_z - ones[i];
            
            max_gain = max({max_gain, gain1, gain2});
        }
        
        return initial_ones + max_gain;
    }
};