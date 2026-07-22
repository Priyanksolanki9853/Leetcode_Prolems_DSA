#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Sparse Table for Range Maximum Queries (RMQ) in O(1) time
class SparseTable {
private:
    int n;
    vector<vector<int>> st;
    vector<int> lg;

public:
    SparseTable() : n(0) {}
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;

        lg.resize(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;
        st.assign(K, vector<int>(n, 0));

        for (int j = 0; j < n; ++j) st[0][j] = nums[j];

        for (int i = 1; i < K; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int i = lg[r - l + 1];
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }
};

class Solution {
    struct Group {
        int start;
        int end;
        int length;
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = count(s.begin(), s.end(), '1'); // Number of '1's across the entire string `s`

        // 1. Identify all zero-groups globally across string `s`
        vector<Group> zeroGroups;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().end = i;
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, i, 1});
                }
            }
        }

        // 2. Map consecutive pairs combining gains
        int numZeroGroups = zeroGroups.size();
        vector<int> adjSums;
        if (numZeroGroups > 1) {
            adjSums.resize(numZeroGroups - 1);
            for (int i = 0; i < numZeroGroups - 1; ++i) {
                adjSums[i] = zeroGroups[i].length + zeroGroups[i + 1].length;
            }
        }
        
        SparseTable st(adjSums);

        vector<int> ans;
        ans.reserve(queries.size());

        // 3. Evaluate max gain localized within boundaries `[l, r]` query-by-query
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            if (numZeroGroups == 0) {
                ans.push_back(total_ones);
                continue;
            }
            
            // Find `A`: First group ending >= l
            int A = -1;
            auto it_A = lower_bound(zeroGroups.begin(), zeroGroups.end(), l, 
                [](const Group& g, int val) {
                    return g.end < val;
                });
            if (it_A != zeroGroups.end()) {
                A = distance(zeroGroups.begin(), it_A);
            }
            
            // Find `B`: Last group starting <= r
            int B = -1;
            auto it_B = upper_bound(zeroGroups.begin(), zeroGroups.end(), r,
                [](int val, const Group& g) {
                    return val < g.start;
                });
            if (it_B != zeroGroups.begin()) {
                B = distance(zeroGroups.begin(), it_B) - 1;
            }
            
            int gain = 0;
            if (A != -1 && B != -1 && A < B) {
                if (A + 1 == B) {
                    // Only two Zero-Groups strictly fall into bounds, they can cleanly combine directly
                    int lenA = zeroGroups[A].end - max(zeroGroups[A].start, l) + 1;
                    int lenB = min(zeroGroups[B].end, r) - zeroGroups[B].start + 1;
                    gain = lenA + lenB;
                } else {
                    // More than two groups. Break it down to evaluate possible highest pairings.
                    int lenA = zeroGroups[A].end - max(zeroGroups[A].start, l) + 1;
                    int lenA_next = zeroGroups[A+1].length;
                    int gain_first = lenA + lenA_next;
                    
                    int lenB = min(zeroGroups[B].end, r) - zeroGroups[B].start + 1;
                    int lenB_prev = zeroGroups[B-1].length;
                    int gain_last = lenB_prev + lenB;
                    
                    int gain_mid = 0;
                    if (A + 1 <= B - 2) {
                        gain_mid = st.query(A + 1, B - 2);
                    }
                    
                    gain = max({gain_first, gain_last, gain_mid});
                }
            }
            
            ans.push_back(total_ones + gain);
        }
        
        return ans;
    }
};