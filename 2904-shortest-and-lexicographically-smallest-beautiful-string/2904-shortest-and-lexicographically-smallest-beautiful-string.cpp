class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        string best = "";
        int left = 0, ones = 0;
        
        for (int right = 0; right < n; right++) {
            if (s[right] == '1') ones++;
            
            // Shrink from left if we have too many 1's
            while (ones > k) {
                if (s[left] == '1') ones--;
                left++;
            }
            
            // If we have exactly k ones, trim leading zeros to minimize length
            if (ones == k) {
                int l = left;
                while (s[l] == '0') l++;
                
                int len = right - l + 1;
                string candidate = s.substr(l, len);
                
                if (best.empty() || len < (int)best.size() || 
                    (len == (int)best.size() && candidate < best)) {
                    best = candidate;
                }
            }
        }
        
        return best;
    }
};