class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char ch : s) cnt[ch - 'a']++;

        // Check palindrome feasibility
        int oddCount = 0, oddChar = -1;
        for (int c = 0; c < 26; c++) {
            if (cnt[c] % 2 != 0) { oddCount++; oddChar = c; }
        }
        if (n % 2 == 0) {
            if (oddCount != 0) return "";
        } else {
            if (oddCount != 1) return "";
        }

        int h = n / 2;
        vector<int> half(26, 0);
        for (int c = 0; c < 26; c++) half[c] = cnt[c] / 2;
        char midChar = (n % 2 == 1) ? ('a' + oddChar) : 0;

        // Case B: try using target's own prefix as the first half
        {
            vector<int> tcnt(26, 0);
            for (int i = 0; i < h; i++) tcnt[target[i] - 'a']++;
            bool matches = true;
            for (int c = 0; c < 26; c++) {
                if (tcnt[c] != half[c]) { matches = false; break; }
            }
            if (matches) {
                string P = target.substr(0, h);
                string T = P;
                if (n % 2 == 1) T += midChar;
                for (int i = h - 1; i >= 0; i--) T += P[i];
                if (T > target) return T;
            }
        }

        // Case A: find the latest divergence position within the first half
        vector<int> remain = half;
        int bestI = -1;
        char bestChar = 0;
        vector<int> bestRemain(26, 0);

        for (int i = 0; i < h; i++) {
            int tc = target[i] - 'a';
            for (int c = tc + 1; c < 26; c++) {
                if (remain[c] > 0) {
                    bestI = i;
                    bestChar = 'a' + c;
                    bestRemain = remain;
                    break;
                }
            }
            if (remain[tc] > 0) {
                remain[tc]--;
            } else {
                break;
            }
        }

        if (bestI == -1) return "";

        string P = target.substr(0, bestI);
        bestRemain[bestChar - 'a']--;
        P += bestChar;
        for (int c = 0; c < 26; c++) {
            P.append(bestRemain[c], 'a' + c);
        }

        string T = P;
        if (n % 2 == 1) T += midChar;
        for (int i = h - 1; i >= 0; i--) T += P[i];

        return T;
    }
};