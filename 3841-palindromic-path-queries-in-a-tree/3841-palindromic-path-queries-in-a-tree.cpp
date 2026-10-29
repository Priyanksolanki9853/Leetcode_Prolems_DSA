class Solution {
    int n;
    vector<int> bit; // Fenwick tree over Euler positions, for XOR

    void add(int pos, int val) {
        for (int i = pos + 1; i <= n + 1; i += i & -i) bit[i] ^= val;
    }
    int prefix(int pos) {
        int r = 0;
        for (int i = pos + 1; i > 0; i -= i & -i) r ^= bit[i];
        return r;
    }

public:
    vector<bool> palindromePath(int n_, vector<vector<int>>& edges, string s, vector<string>& queries) {
        n = n_;
        const int LOG = 17; // 2^17 > 5 * 10^4

        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> tin(n), tout(n), depth(n, 0), base(n), idx(n, 0);

        // iterative DFS from root 0
        int timer = 0;
        vector<int> st = {0};
        base[0] = 1 << (s[0] - 'a');
        tin[0] = timer++;
        while (!st.empty()) {
            int u = st.back();
            if (idx[u] < (int)g[u].size()) {
                int v = g[u][idx[u]++];
                if (v == up[0][u]) continue; // skip parent
                up[0][v] = u;
                depth[v] = depth[u] + 1;
                base[v] = base[u] ^ (1 << (s[v] - 'a'));
                tin[v] = timer++;
                st.push_back(v);
            } else {
                tout[u] = timer - 1;
                st.pop_back();
            }
        }

        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++)
                up[j][v] = up[j - 1][up[j - 1][v]];

        auto lca = [&](int a, int b) {
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int j = 0; j < LOG; j++)
                if (diff >> j & 1) a = up[j][a];
            if (a == b) return a;
            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][a] != up[j][b]) {
                    a = up[j][a];
                    b = up[j][b];
                }
            }
            return up[0][a];
        };

        auto pref = [&](int x) { return base[x] ^ prefix(tin[x]); };

        bit.assign(n + 2, 0);
        vector<bool> ans;

        for (const string& q : queries) {
            istringstream in(q);
            string op;
            in >> op;
            if (op == "update") {
                int u;
                char c;
                in >> u >> c;
                if (s[u] != c) {
                    int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                    add(tin[u], delta);          // range XOR over u's subtree
                    add(tout[u] + 1, delta);
                    s[u] = c;
                }
            } else {
                int u, v;
                in >> u >> v;
                int l = lca(u, v);
                int mask = pref(u) ^ pref(v) ^ (1 << (s[l] - 'a'));
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};