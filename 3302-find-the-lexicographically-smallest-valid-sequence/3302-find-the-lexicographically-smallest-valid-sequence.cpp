class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        // R[k] will store the starting index in word1 of the rightmost exact match of word2[k...m-1]
        vector<int> R(m + 1, -1);
        R[m] = n;
        
        int curr = n - 1;
        for (int k = m - 1; k >= 0; --k) {
            if (curr < 0) {
                R[k] = -1;
                continue;
            }
            int p = curr;
            while (p >= 0 && word1[p] != word2[k]) {
                p--;
            }
            if (p >= 0) {
                R[k] = p;
                curr = p - 1;
            } else {
                R[k] = -1;
                curr = -1;
            }
        }
        
        vector<int> seq;
        seq.reserve(m);
        int last_j = -1;
        bool changed = false;
        
        // Greedily build the lexicographically smallest sequence
        for (int i = 0; i < m; ++i) {
            if (changed) {
                // Change has been used, we are forced to pick the earliest exact match
                int exact_j = -1;
                for (int j = last_j + 1; j < n; ++j) {
                    if (word1[j] == word2[i]) {
                        exact_j = j;
                        break;
                    }
                }
                if (exact_j == -1) return {};
                seq.push_back(exact_j);
                last_j = exact_j;
            } else {
                // If picking the immediately next index allows the rest of the word to be exactly matched...
                if (last_j + 1 < R[i + 1]) {
                    int j = last_j + 1;
                    seq.push_back(j);
                    if (word1[j] != word2[i]) {
                        changed = true; // Use up our 1 allowance
                    }
                    last_j = j;
                } else {
                    // Otherwise, we are forced to conserve the change and find the earliest exact match
                    int exact_j = -1;
                    for (int j = last_j + 1; j < n; ++j) {
                        if (word1[j] == word2[i]) {
                            exact_j = j;
                            break;
                        }
                    }
                    if (exact_j == -1) return {};
                    seq.push_back(exact_j);
                    last_j = exact_j;
                }
            }
        }
        
        return seq;
    }
};