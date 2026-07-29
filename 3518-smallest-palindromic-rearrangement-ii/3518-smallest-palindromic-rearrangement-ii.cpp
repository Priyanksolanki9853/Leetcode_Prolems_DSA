class Solution {
public:
    long long capped_nCr(int n, int r, long long cap) {
        if (r < 0 || r > n) return 0;
        if (r > n / 2) r = n - r; 
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            long long num = n - i + 1;
            res = res * num / i;
            if (res > cap) return cap + 1;
        }
        return res;
    }
    
    long long calculate_perms(const vector<int>& counts, long long cap) {
        int L = 0;
        for (int c : counts) L += c;
        
        long long total = 1;
        for (int c : counts) {
            if (c == 0) continue;
            long long combinations = capped_nCr(L, c, cap);
            
            if (total > cap / combinations + 1) {
                return cap + 1;
            }
            total *= combinations;
            if (total > cap) return cap + 1;
            
            L -= c;
        }
        return total;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        vector<int> counts(26, 0);
        string mid_char = "";
        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 != 0) {
                mid_char = string(1, 'a' + i);
            }
            counts[i] = freq[i] / 2;
        }
        
        long long cap = k;
        if (calculate_perms(counts, cap) < k) {
            return "";
        }
        
        string left_half = "";
        int L = 0;
        for (int c : counts) L += c;
        
        while (L > 0) {
            for (int i = 0; i < 26; ++i) {
                if (counts[i] > 0) {
                    counts[i]--;
                    
                    long long W = calculate_perms(counts, cap);
                    
                    if (k <= W) {
                        left_half += (char)('a' + i);
                        L--;
                        break; 
                    } else {
                        k -= W;
                        counts[i]++;
                    }
                }
            }
        }
        
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        
        return left_half + mid_char + right_half;
    }
};