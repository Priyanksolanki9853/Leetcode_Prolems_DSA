class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26, -1), last(26, -1);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] == -1) first[c] = i;
            last[c] = i;
        }

        vector<pair<int,int>> intervals; 
        for (int i = 0; i < n; i++) {
            if (first[s[i] - 'a'] != i) continue; 

            int right = last[s[i] - 'a'];
            int j = i;
            bool valid = true;
            while (j <= right) {
                int c = s[j] - 'a';
                if (first[c] < i) { valid = false; break; }
                right = max(right, last[c]);
                j++;
            }
            if (valid) intervals.push_back({i, right});
        }

        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
            if (a.second != b.second) return a.second < b.second;
            return a.first > b.first;
        });

        vector<string> result;
        int lastEnd = -1;
        for (auto& [st, en] : intervals) {
            if (st > lastEnd) {
                result.push_back(s.substr(st, en - st + 1));
                lastEnd = en;
            }
        }
        return result;
    }
};