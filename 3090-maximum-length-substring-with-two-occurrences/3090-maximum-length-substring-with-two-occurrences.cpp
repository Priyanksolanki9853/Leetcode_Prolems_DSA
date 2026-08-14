class Solution {
public:
    int maximumLengthSubstring(std::string s) {
        int count[26] = {0}; // Frequency array for lowercase English letters
        int ans = 0;
        int i = 0;
        
        for (int j = 0; j < s.length(); ++j) {
            int c = s[j] - 'a';
            count[c]++;
            
            // Shrink the window from the left if any character exceeds 2 occurrences
            while (count[c] > 2) {
                count[s[i] - 'a']--;
                i++;
            }
            
            // Update the maximum length of the valid window
            ans = std::max(ans, j - i + 1);
        }
        
        return ans;
    }
};