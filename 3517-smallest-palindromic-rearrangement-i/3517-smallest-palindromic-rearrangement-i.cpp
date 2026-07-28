class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26, 0);
        
        for (char c : s) {
            count[c - 'a']++;
        }
        
        string left_half = "";
        string mid = "";
        
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                mid = string(1, i + 'a');
            }
            left_half += string(count[i] / 2, i + 'a');
        }
        
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + mid + right_half;
    }
};