class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> target_counts(128, 0);
        for (char c : t) {
            target_counts[c]++;
        }
        
        int left = 0, min_left = 0, min_len = INT_MAX;
        int required = t.length();
        
        for (int right = 0; right < s.length(); ++right) {
            if (target_counts[s[right]] > 0) {
                required--;
            }
            target_counts[s[right]]--;
            
            while (required == 0) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    min_left = left;
                }
                
                target_counts[s[left]]++;
                if (target_counts[s[left]] > 0) {
                    required++;
                }
                left++;
            }
        }
        
        return min_len == INT_MAX ? "" : s.substr(min_left, min_len);
    }
};