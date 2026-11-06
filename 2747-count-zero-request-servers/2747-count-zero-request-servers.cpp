class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int q = queries.size();
        vector<int> order(q);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return queries[a] < queries[b];
        });

        vector<int> cnt(n + 1, 0);
        int active = 0;
        int left = 0, right = 0;
        int m = logs.size();

        vector<int> ans(q);
        for (int idx : order) {
            int hiT = queries[idx];
            int loT = hiT - x;

            while (right < m && logs[right][1] <= hiT) {
                if (cnt[logs[right][0]]++ == 0) active++;
                right++;
            }
            while (left < right && logs[left][1] < loT) {
                if (--cnt[logs[left][0]] == 0) active--;
                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};