class Solution {
    const long long MOD = 1e9 + 7;
    vector<long long> s, q, lz; 

    void apply(int o, int len, long long v) {
        q[o] = (q[o] + 2 * v % MOD * s[o] + v * v % MOD * len) % MOD; 
        s[o] = (s[o] + v * len) % MOD;
        lz[o] = (lz[o] + v) % MOD;
    }

    void push(int o, int l, int r) {
        if (lz[o]) {
            int m = (l + r) / 2;
            apply(2 * o, m - l + 1, lz[o]);
            apply(2 * o + 1, r - m, lz[o]);
            lz[o] = 0;
        }
    }

    void update(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply(o, r - l + 1, 1);
            return;
        }
        push(o, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update(2 * o, l, m, ql, qr);
        if (qr > m) update(2 * o + 1, m + 1, r, ql, qr);
        s[o] = (s[2 * o] + s[2 * o + 1]) % MOD;
        q[o] = (q[2 * o] + q[2 * o + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        s.assign(4 * n, 0);
        q.assign(4 * n, 0);
        lz.assign(4 * n, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            update(1, 0, n - 1, last[nums[i]] + 1, i);
            last[nums[i]] = i;
            ans = (ans + q[1]) % MOD; 
        }

        return (int)ans;
    }
};