class Solution {
public:
    std::string smallestSubsequence(std::string s) {
        // Track the last index where each character appears
        std::vector<int> last_occurrence(26, 0);
        for (int i = 0; i < s.length(); ++i) {
            last_occurrence[s[i] - 'a'] = i;
        }
        
        // Track characters currently in our result stack
        std::vector<bool> seen(26, false);
        std::string result = "";
        
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            
            // If the character is already in our result string, skip it
            if (seen[c - 'a']) {
                continue;
            }
            
            // While result is not empty AND the current character is smaller 
            // than the last character in result AND the last character appears again later:
            while (!result.empty() && c < result.back() && last_occurrence[result.back() - 'a'] > i) {
                // Mark the removed character as unseen
                seen[result.back() - 'a'] = false;
                result.pop_back();
            }
            
            // Add the current character and mark it as seen
            result.push_back(c);
            seen[c - 'a'] = true;
        }
        
        return result;
    }
};