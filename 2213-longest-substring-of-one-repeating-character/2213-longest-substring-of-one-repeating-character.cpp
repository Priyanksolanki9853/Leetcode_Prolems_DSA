class Solution {
    struct Node {
        int max_len = 0, pref_len = 0, suff_len = 0, len = 0;
        char pref_char = 0, suff_char = 0;
    };

    vector<Node> tree;
    
    Node merge(const Node& left, const Node& right) {
        if (left.len == 0) return right;
        if (right.len == 0) return left;
        
        Node res;
        res.len = left.len + right.len;
        res.pref_char = left.pref_char;
        res.suff_char = right.suff_char;
        
        res.pref_len = left.pref_len;
        if (left.pref_len == left.len && left.pref_char == right.pref_char) {
            res.pref_len += right.pref_len;
        }
        
        res.suff_len = right.suff_len;
        if (right.suff_len == right.len && right.suff_char == left.suff_char) {
            res.suff_len += left.suff_len;
        }
        
        res.max_len = max({left.max_len, right.max_len, res.pref_len, res.suff_len});
        if (left.suff_char == right.pref_char) {
            res.max_len = max(res.max_len, left.suff_len + right.pref_len);
        }
        
        return res;
    }
    
    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node].max_len = tree[node].pref_len = tree[node].suff_len = tree[node].len = 1;
            tree[node].pref_char = tree[node].suff_char = s[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    
    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node].pref_char = tree[node].suff_char = c;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }
    
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n + 1);
        build(1, 0, n - 1, s);
        
        int k = queryIndices.size();
        vector<int> ans(k);
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans[i] = tree[1].max_len;
        }
        return ans;
    }
};