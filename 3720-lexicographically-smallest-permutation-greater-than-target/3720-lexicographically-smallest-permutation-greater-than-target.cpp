class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        vector<int> remain = cnt;
        int bestI = -1;
        char bestChar = 0;
        vector<int> bestRemain(26, 0);

        for (int i = 0; i < n; i++) {
            int tc = target[i] - 'a';

            // Look for the smallest available character strictly greater than target[i]
            for (int c = tc + 1; c < 26; c++) {
                if (remain[c] > 0) {
                    bestI = i;
                    bestChar = 'a' + c;
                    bestRemain = remain;  // snapshot of counts at this point
                    break;
                }
            }

            // Try to consume target[i] to keep matching the prefix
            if (remain[tc] > 0) {
                remain[tc]--;
            } else {
                break;  // can't match prefix any further
            }
        }

        if (bestI == -1) return "";

        string result = target.substr(0, bestI);
        bestRemain[bestChar - 'a']--;
        result += bestChar;

        for (int c = 0; c < 26; c++) {
            result.append(bestRemain[c], 'a' + c);
        }

        return result;
    }
};